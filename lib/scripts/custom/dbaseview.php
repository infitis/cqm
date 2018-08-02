<?php
// Path to dbase file
$db_file = $argv[1];

if (!extension_loaded('dbase')) {
    die("dbase extensions not loaded.\n");
}

// Open dbase file
$dbh = dbase_open($db_file, 2);

//show column names
$column_info = dbase_get_record_with_names($dbh, 1);
reset($column_info);
do
{
    print key($column_info)."\t";
}
while (next($column_info));
print "\n";

//show data
$numrec = dbase_numrecords($dbh);
for ($j=1; $j<=$numrec; $j++)
{
    $rec = dbase_get_record($dbh, $j);
    $nf  = dbase_numfields($dbh);
    for ($i=0; $i < $nf; $i++)
    {
        print $rec[$i]."\t";
    }
    print "\n";
}

//close dbase file
dbase_close($dbh);
?>
