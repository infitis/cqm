<?php

$db = mysql_connect("localhost", "root", "") or die("Could not connect : " . mysql_error());
mysql_select_db("oldstash", $db);

$oldtables = array("4", "5");

$n = "use stash;;\n";
$scount = 0;
$filename = "oldvagons.sql";

foreach ($oldtables as $oldtable)
{
    $q  ="select * from vagons".$oldtable;
    $res=mysql_query($q) or die(mysql_error());

    while ($row = mysql_fetch_array($res, MYSQL_NUM))
    {
        $u = "insert into vagons set vname='v$oldtable', coaltype=0, ";

        $u .= "moment='".$row[0]."', ";
        $u .= "p='".     $row[2]."', ";
        $u .= "a='".     $row[3]."', ";
        $u .= "number='".$row[4]."', ";
        $u .= "cert='".  $row[5]."', ";
        $u .= "pos='".   $row[6]."', ";
        $u .= "rwdate='".$row[7]."', ";
        $u .= "wei='".   $row[8]."';;\n";
        $n .= $u;
        $scount++;
    }
    
    mysql_free_result($res);

    print "table vagons$oldtable: $scount rows\n";
    $scount = 0;

}

mysql_close($db);


if (!$fh = fopen($filename, 'w'))
{
    print "Cannot open file $filename\n";
    exit;
}

//real writing
fwrite($fh, $n);

//close outputfile
fclose($fh);




?>