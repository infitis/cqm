#!/usr/bin/php
<?php
#  MAGULA
#  Copyright  (c) Ruslan Keba, 2004
#             mailto:rk@kometalab.com.ua
#             http://www.kometalab.com.ua
#  file:      mcro.php
#             make check, repair, optimize for mysql database

include "mconf.inc.php";

/*check db name*/
if ($m_db == "")
{
   $m_db = $m_arg;
}

if ($m_db == "")
{
   diecode(1,"no database.");
}

/*connecting to server*/
if ($m_verb) print "connecting...";
$db = mysql_connect($m_host, $m_user, $m_pswd) or diecode(3,"Could not connect : " . mysql_error());
if ($m_verb) print "        ok.\n";

/*selecting databse*/
mysql_select_db($m_db) or diecode(4, "Could not select database.");

//get all table names
$q = "SHOW TABLES";
$allt = mysql_query($q) or diecode(5,"Query failed : " . mysql_error());

//for each table
if ($m_verb) print ("tables:\n");
while ($buf1 = mysql_fetch_array($allt, MYSQL_ASSOC))
{
    foreach ($buf1 as $tn)
    {
        if ($m_verb) print "\t$tn\n";

        //check table
        $q = "CHECK TABLE $tn;";
        $r = mysql_query($q) or diecode(6,"Query failed : " . mysql_error());

        //check last row for table status
        mysql_data_seek($r, mysql_num_rows($r) - 1);
        $row = mysql_fetch_array($r, MYSQL_ASSOC);

        if (!($row["Msg_text"] == "OK" || $row["Msg_text"] == "Not checked"))
        {
            print "\t$tn\n";
            print "\t\t".$row["Msg_type"]." = ".$row["Msg_text"]."\n";
            //corrupted table, try repair
            print "\t\tTable corrupted! Trying repair.\n";
            logmsg("mcro  : table $tn CORRUPTED!");
            $repair = mysql_query("REPAIR TABLE $tn;") or print("Query failed : " . mysql_error());

            while ($rrow = mysql_fetch_array($repair, MYSQL_ASSOC))
            {
                $t = $rrow["Table"]."\t".$rrow["Op"]."\t".$rrow["Msg_type"]."\t".$rrow["Msg_text"];

                print($t."\n");
                logmsg($t);
            }

            mysql_free_result($repair);
        }

        mysql_free_result($r);

        $q = "OPTIMIZE TABLE $tn;";
        $r = mysql_query($q) or diecode(7, "Query failed : " . mysql_error());
        mysql_free_result($r);
    }
}

//Free resultset
mysql_free_result($allt);

//disconnecting from database
mysql_close($db);
if ($m_verb) print "cro...           ok.\n";

exit(0);

?>
