#!/usr/bin/php
<?php
/*
  MAGULA
  Copyright  (c) Ruslan Keba, 2004
             mailto:rk@kometalab.com.ua
             http://www.kometalab.com.ua
  file:      mbu.php
             make backup copy mysql database
*/

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

if (count($m_backup_dir) === 0)
{
    diecode(2,"no backup dir.");
}

/*connecting to server*/
if ($m_verb) print "connecting...    ";
$db = mysql_connect($m_host, $m_user, $m_pswd) or diecode(3,"Could not connect : " . mysql_error());
if ($m_verb) print "    ok.\n";

/*selecting databse*/
mysql_select_db($m_db) or diecode(4,"Could not select database.");

/*open output file*/
if ($m_no_data)
{
    $filename = "$m_db.create.sql";
}
else
{
    $filename = "$m_db.sql";
}

if ($m_verb) print "Output file: $filename.gz\n";
if ($m_no_data)
{
    if ($m_verb) print "no rows, only creation info\n";
}

//sql-content for output
$out = "";
$was_error = 0;

/*write header*/
$out .= "# magula mysql database backup$m_qdiv
CREATE DATABASE IF NOT EXISTS $m_db$m_qdiv
USE $m_db$m_qdiv
";

/*get all table names*/
$q = "SHOW TABLES";
$allt = mysql_query($q) or diecode(5,"Query failed : " . mysql_error());

/*for each table*/
if ($m_verb) print ("tables:\n");
while ($buf1 = mysql_fetch_array($allt, MYSQL_ASSOC))
{
    foreach ($buf1 as $tn)
    {
        if ($m_verb) print "\t$tn\n";
        $out .= "\n# TABLE $tn$m_qdiv\n";

        //create table
        $q = "SHOW CREATE TABLE $tn;";
        $r = mysql_query($q);
        if (!$r)
        {
            print("Query failed : " . mysql_error());
            $was_error++;
            $out .= "\n#    CREATE FOR TABLE $tn CORRUPTED\n";
            logmsg("mbu   : Create information for table $tn corrupted.");
            continue;
        }
        $a = mysql_fetch_array($r, MYSQL_ASSOC);
        //drop table
        $out .= "DROP TABLE IF EXISTS $tn$m_qdiv\n";
        $out .= $a["Create Table"]."$m_qdiv\n";
        mysql_free_result($r);

        //data dump
        if (!$m_no_data)
        {
            $r = mysql_query("SELECT * FROM $tn");
            if (!$r)
            {
                print("Query failed : " . mysql_error());
                $was_error++;
                $out .= "\n#    DATA FOR TABLE $tn CORRUPTED\n";
                logmsg("mbu   : Data for table $tn corrupted.");
                continue;
            }
            while ($buf2 = mysql_fetch_array($r, MYSQL_ASSOC))
            {
                $str = "";
                $out .= "INSERT INTO $tn VALUES (";
                foreach ($buf2 as $data)
                {
                    $str = $str."'$data',";
                }
                $str = substr($str, 0, strlen($str)-1);
                $out .=  "$str)$m_qdiv\n";
            }
            mysql_free_result($r);
        }
    }
}


//Free result
mysql_free_result($allt);

//check for corrupted
if ($was_error)
{
    print "backup is not complete: $was_error error(s)\nwriting corrupted version\n";
    //corrupted filename
    $badfilename = str_replace(".sql", ".corrupted.sql", $filename);
    $filename = $badfilename;
}

if (!$fh = fopen($filename, 'w'))
{
    print "Cannot open file $filename\n";
    exit(6);
}

//real writing
fwrite($fh, $out);

//close outputfile
fclose($fh);

/*disconnecting from database*/
mysql_close($db);
if ($m_verb) print "backup...            ok.\n";

/*zip outputfile*/
if (!extension_loaded('zlib'))
{
    print ("zlib extension not loaded. try use system gzip.");
    shell_exec("$m_gzip -9 $filename");
}
else
{
    //get content
    $fh = fopen ($filename, "r");
    $content = fread ($fh, filesize ($filename));
    fclose ($fh);

    //open file for writing with maximum compression
    $zp = gzopen($filename.".gz", "w9");

    //write string to file
    gzwrite($zp, $content);

    //close file
    gzclose($zp);
}

if ($m_verb) print "coping to...\n";
foreach($m_backup_dir as $bu_dir)
{
    if ($m_verb) print "\t$bu_dir\n";
    //check dir
    if (!file_exists($bu_dir))
    {
        mkdir($bu_dir);
        print "make dir $bu_dir.\n";
    }

    //previous backup
    $prevfilename = str_replace(".sql", ".prev.sql", $filename);
    
    if (file_exists("$bu_dir/$filename.gz"))
    {
        if (file_exists("$bu_dir/$prevfilename.gz"))
        {
            unlink("$bu_dir/$prevfilename.gz");
        }
        //rename current old version to previous
        rename("$bu_dir/$filename.gz", "$bu_dir/$prevfilename.gz");
    }

    //remove gz file in backup dir
    copy("$filename.gz", "$bu_dir/$filename.gz");
}
if ($m_verb) print "                     ok.\n";

//delete sql-file & gz
if (file_exists($filename))
{
    unlink($filename);
}
unlink($filename.".gz");

exit(0);

?>
