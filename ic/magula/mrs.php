#!/usr/bin/php
<?php
/*
  MAGULA
  Copyright  (c) Ruslan Keba, 2004
             mailto:rk@kometalab.com.ua
             http://www.kometalab.com.ua
  file:      mrs.php
             restore backup copy mysql database or execute script
*/

include "mconf.inc.php";

//check db name
if ($m_db == "")
{
   $m_db = $m_arg;
}

if ($m_db == "")
{
   diecode(1,"no database.");
}

$contents = "";

//open input file
foreach($m_backup_dir as $bu_dir)
{
    $filename = "$bu_dir/$m_db.sql.gz";
    if ($m_verb) print "input file: $filename\n";
    if (!file_exists($filename))
    {
        diecode(2,"File not exists.\n");
    }

    //unzip outputfile

    if (!extension_loaded('zlib'))
    //if (1) //use only external gzip!
    {
        print ("zlib extension not loaded. try use system gzip.\n");
        shell_exec("$m_gzip -d $filename");

        $filename = "$bu_dir/$m_db.sql";
        if (!$fp = fopen($filename, 'r'))
        {
            diecode(3,"Could not open file $filename\n");
        }

        //read gzip content
        print "system decompress...\n";
        $contents = fread ($fp, filesize($filename));
        fclose ($fp);

        //compress decompressed file
        print "try again compress $filename...\n";
        shell_exec("$m_gzip -9 $filename");

    }
    else
    {
        if (!$zp = gzopen($filename, 'r'))
        {
            diecode(4,"Could not open file $filename\n");
        }

        //read gzip content
        if ($m_verb) print "decompress...   ";
        $contents = gzread ($zp, $max_gzip_file_size);
        gzclose ($zp);
    }

    if ($contents)
    {
        if ($m_verb) print "ok.\n";
        break;
    }
    if ($m_verb) print "        bad, try next backup directory.\n";
}

if (!$contents)
{
    diecode(5,"Could not get backup.\n");
}

//print "contents lenght is ".strlen($contents)."\n";

//connecting to server
if ($m_verb) print "connecting...";
$db = mysql_connect($m_host, $m_user, $m_pswd) or diecode(6,"Could not connect : " . mysql_error());
if ($m_verb) print "    ok.\n";

//split to querys and execute
if ($m_verb) print "split to queries and execute...\n";

$errors = 0;
$queries= 0;
$q = "";
$s = "";

$prevchr = 0;

for ($i=0; $i<strlen($contents)-1; $i++)
{
    if (  $contents{$i}   == $m_qdiv && 
         ($contents{$i+1} == $m_qdiv ||
          $contents{$i+1} == "\n"    ||
          $contents{$i+1} == "\r")
       )
    {
        //get query
        $s = substr($contents, $prevchr, $i-$prevchr);
        $i++;
        $prevchr = $i;

        //move semicolons
        $q = trim($s, ";\t\n\r ");

        if ($q == "")
        {
            continue;
        }

        //executing
        $r = mysql_query($q);
        if (!$r)
        {
            $errors++;
            print("query: $q\nerror:".mysql_error()."\n");
        }
        else
        {
            $queries++;
        }
    }
}

if ($m_verb) print "done with $errors error(s).\n";
if ($m_verb) print "queries executed: $queries.\n";

//disconnecting from database
mysql_close($db);

exit(0);

?>
