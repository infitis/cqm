#!/usr/bin/php
<?php
/*
    ________
    usage:
    dbpacker.php <database> <table> <where_cond> <startday> <stopday>
    ________
    sample:
    dbpacker.php starobesh points point='1a' -65 -40
      pack all records in table starobesh.points 
      where point='1a' between 65 and 40 day ago
    ________
    Copyright (c) Ruslan Keba 2004
*/

$PACKER_VERSION = "2.1-beta";

function df($dts)
{
    return date("YmdHis", $dts);
}


if ($argc < 6)
    die("too few params.");

//options from args
$dbname= $argv[1];
$table = $argv[2];
$cond  = $argv[3];
$start = $argv[4];
$stop  = $argv[5];

//mysq options
$m_host = "localhost";
$m_user = "root";
$m_pswd = "";

//Coal & CoalHeap classes
include "coalheap.php";

print "cqm database packer $PACKER_VERSION\n";

/*connecting to server*/
$db = mysql_connect($m_host, $m_user, $m_pswd) or die("Could not connect : " . mysql_error());

/*selecting databse*/
mysql_select_db($dbname) or die("Could not select database.");

$atoday = getdate(); 
$today = mktime(0, 0, 0, $atoday["mon"], $atoday["mday"], $atoday["year"]);
print "today: ".date("Y-m-d", $today)."\n";

//main day cycle
for ($i=$start; $i<=$stop; $i++)
{
    $day = $today + $i*24*60*60;
    print "day: ".date("Y-m-d", $day)."\n";
    //hours cycle
    for ($h=0; $h<=23; $h++)
    {
        $lo= $day + $h*60*60;
        $hi= $day + ($h+1)*60*60;
        
        //records number in this hour
        $q = "select count(*) as c from $table where $cond and moment>'".df($lo)."' and moment<='".df($hi)."'";
        //print $q."\n";
        $r = mysql_query($q);
        $a = mysql_fetch_array($r, MYSQL_ASSOC);
        $c = $a["c"];
        if ($c <=2 )
            continue;
        print "  hour: $h, records: $c\n";
        mysql_free_result($r);


        //summary weight & ash
        $q = "select p,a from $table where $cond and moment>'".df($lo)."' and moment<='".df($hi)."'";
        //print $q."\n";
        $r = mysql_query($q);

        $heap = new CoalHeap;

        while ($row = mysql_fetch_array($r, MYSQL_ASSOC))
        {
            //print "(".$row["p"].",".$row["a"].")\n";
            $co = new Coal($row["p"], $row["a"], 0);
            //print "      coal (".$co->P.",".$co->A.")\n";
            $heap->addCoal($co);
            //print "      heap (".$heap->c->P.",".$heap->c->A.")\n";
            unset($co);
        }
        mysql_free_result($r);

        //delete this records
        $q = "delete from $table where $cond and moment>'".df($lo)."' and moment<='".df($hi)."'";
        $r = mysql_query($q);
        if (!$r)
            print "    ! sql delete error!\n";

        //insert once new value p, a
        if (($heap->c->P < P_MIN && $heap->c->A < A_MIN) ||
            (!$heap->c->P && !$heap->c->A))
        {
            print "    p=0 & a=0 (idle or empty) - don`t write it\n";
        }
        else
        {
            print "    p=".$heap->c->P.", a=".$heap->c->A."\n";

            $wtime = date("YmdHis", $day+($h+1)*60*60-1);
            $wp = $heap->c->P;
            $wa = $heap->c->A;
            if (is_null($wp)) $wp = "NULL";
            if (is_null($wa)) $wa = "NULL";

            $q = "insert into $table set $cond, moment='".$wtime."', p=".$wp.", a=".$wa;
            //print $q."\n";
            $r = mysql_query($q);
            if (!$r)
                print "    ! sql insert error!\n";
        }
    }
}

mysql_close($db);

?>