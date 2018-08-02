<?php

/*point names*/
$pin  = array();
$pout = array();

/*mysql options*/
$m_host = "localhost";
$m_user = "root";
$m_pswd = "";
$m_dbname = $argv[1];

/*Coal & CoalHeap classes*/
include "coalheap.php";


/*get point names*/
for ($i=2; $i<$argc; $i++)
{
    $ch = substr($argv[$i], 0, 1);
    if ($ch == '+')
    {
        array_push($pin, substr($argv[$i], 1));
    }
    if ($ch == '-')
    {
        array_push($pout, substr($argv[$i], 1));
    }

}


print "cqm point balance: ".date("Y-m-d H:i:s")."\n";

/*connecting to server*/
$db = mysql_connect($m_host, $m_user, $m_pswd) or die("Could not connect : " . mysql_error());

/*selecting databse*/
mysql_select_db($m_dbname) or die("Could not select database.");

$hin  = new CoalHeap();
$hout = new CoalHeap();

foreach($pin as $p)
{
    addcoal($hin, $p);
}

foreach($pout as $p)
{
    addcoal($hout, $p);
}

print "+ ".$hin->format()."\n";
print "- ".$hout->format()."\n";

unset($hout);
unset($hin);

mysql_close($db);

/*add coal from point to heap*/
function addcoal(&$heap, $point)
{
    $atoday = getdate(); 
    $today  = mktime(0, 0, 0, $atoday["mon"], $atoday["mday"], $atoday["year"]);
    $d = date("YmdHis", $today);

    $q = "select p,a from points where point='$point' and a is not null and p is not null and moment > date_sub('$d', interval 1 day) and moment <= '$d'";
    $r = mysql_query($q);

    while ($row = mysql_fetch_array($r, MYSQL_ASSOC))
    {
        $co = new Coal($row["p"], $row["a"], 0);
        $heap->addCoal($co);
        unset($co);
    }

    mysql_free_result($r);

}


?>