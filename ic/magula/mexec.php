#!/usr/bin/php
<?php
/*
  MAGULA
  Copyright  (c) Ruslan Keba, 2004
             mailto:rk@kometalab.com.ua
             http://www.kometalab.com.ua
  file:      exec.php
             execute sql-script
*/

include "mconf.inc.php";
$contents = "";

//check file name
if ($m_file == "")
{
   $m_file = $m_arg;
}
if ($m_file == "")
{
   diecode(1,"no input file.\n");
}

//open input file
$filename = $m_file;
if ($m_verb) print "input file: $filename\n";
if (!file_exists($filename))
{
    diecode(2, "File not exists.\n");
}

//extension of file
$exts = explode(".", $filename);
$ext = end($exts);
if ($ext == "gz")
{
    //need unzip outputfile
    if (!extension_loaded('zlib'))
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
        if ($m_verb) print "decompress...";
        $contents = gzread ($zp, $max_gzip_file_size);
        gzclose ($zp);
    }

    if (!$contents)
    {
        diecode(5,"        can`t unzip $filename.\n");
    }
    else
    {
        if ($m_verb) print("        ok.\n");
    }
}
else
{
    $fh = fopen($filename, "r");
    if (!$fh)
    {
        diecode(6,"Could not open file $filename\n");
    }
    $contents = fread($fh, filesize($filename));
    fclose($fh);
}


if (!$contents)
{
    diecode(7,"Could not get content of.\n");
}

//connecting to server
if ($m_db != "")
{
    $m_db = "mysql";
}

if ($m_verb) print "connecting...";
$db = mysql_connect($m_host, $m_user, $m_pswd) or diecode(8,"Could not connect : " . mysql_error());
if ($m_verb) print "        ok.\n";

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
