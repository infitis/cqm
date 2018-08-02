<?
$db = mysql_connect("localhost", "root", "") or die("Could not connect : " . mysql_error());
mysql_select_db("blagodat") or die("Could not select database.");

$A = array();
$As = 0;
$n = 0;
$S = 0;
$D = 0;

$q = "SELECT a FROM points WHERE point='p116' AND moment>20050423180000 AND moment<20050424060000 AND a>0 AND a IS NOT NULL order by moment";

$allt = mysql_query($q) or die("Query failed : " . mysql_error());
while ($buf1 = mysql_fetch_array($allt, MYSQL_ASSOC))
{
    foreach ($buf1 as $row)
    {
    	$As = $As + $row;
    	$n++;
    }
}

$As = $As / $n;
print "n = $n\n";
print "As = $As\n";


$allt = mysql_query($q) or die("Query failed : " . mysql_error());
while ($buf1 = mysql_fetch_array($allt, MYSQL_ASSOC))
{
    foreach ($buf1 as $row)
    {
    	$S = $S + ($As - $row)*($As - $row);
    }
}

$D = sqrt($S/($n - 1));
print "D = $D\n";


mysql_close($db);

?>