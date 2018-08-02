<?php
/*
  MAGULA
  Copyright  (c) Ruslan Keba, 2004
             mailto:rk@kometalab.com.ua
             http://www.kometalab.com.ua
  file:      mconf.inc.php
             included file with general configuration
*/

//error reporting
error_reporting  (E_ALL);

/*define global variables*/
$m_name    = "Magula";
$m_version = "1.4.0-stable-win";

$m_host    = "localhost";
$m_port    = 3306;
$m_db      = "";
$m_user    = "root";
$m_pswd    = "";
$m_file    = "";

/*for log*/
$m_logfilename = "magula.log";
$m_log     = "";


/*default argument*/
$m_arg     = "";

/*no rows, only creation info (for mbu)*/
$m_no_data = FALSE;

/*verbose*/
$m_verb = FALSE;

/*path to zgip compressor*/
$m_gzip    = "gzip";

$max_gzip_file_size = 41943040;//40M

$m_backup_dir = array(
# "d:\\projects\\magula\\backup"
#, more paths...
);

/*query divider*/
$m_qdiv = ';';


function print_help()
{
global $m_name, $m_version;
echo <<< END
$m_name $m_version
Copyright (c) Ruslan Keba, 2004
mailto:rk@kometalab.com.ua
usage: <mscript>.php <target> [options]
mscript = mbu | mrs | mrp | mexec
target  = databasename | sql-script
options =
  -?        print this help;
  -h<host>  mysql server host (default = localhost);
  -o<port>  mysql server port (default = 3306);
  -d<db>    mysql database name;
  -u<user>  mysql user name   (default = root);
  -p<pswd>  mysql password    (default = '');
  -b<path>  path to backup files;
  -n        no rows for backup, only creation info.
  -f<file>  path to sql-script for mexec.php
  -v        verbose

END;
}


/*check option*/
for ($i=1; $i<$argc; $i++)
{
    $option       = substr($argv[$i], 0, 2);
    $first_leter  = substr($argv[$i], 0, 1);
    if ($first_leter != "-")
    {
       $m_arg = $argv[$i];
       continue;
    }
    if ($option == "-?")
    {
       print_help();
       die();
    }
    if ($option == "-h")
    {
       $m_host = substr($argv[$i], 2);
       continue;
    }
    if ($option == "-o")
    {
       $m_port = substr($argv[$i], 2);
       continue;
    }
    if ($option == "-d")
    {
       $m_db = substr($argv[$i], 2);
       continue;
    }
    if ($option == "-u")
    {
       $m_user = substr($argv[$i], 2);
       continue;
    }
    if ($option == "-p")
    {
       $m_pswd = substr($argv[$i], 2);
       continue;
    }
    if ($option == "-b")
    {
       $bupath = substr($argv[$i], 2);
       array_push($m_backup_dir, $bupath);
       continue;
    }
    if ($option == "-n")
    {
       $m_no_data = TRUE;
       continue;
    }
    if ($option == "-f")
    {
       $m_file = substr($argv[$i], 2);
       continue;
    }
    if ($option == "-v")
    {
       $m_verb = TRUE;
       continue;
    }
}

function logmsg($s)
{
    global $m_logfilename;
    $flog = fopen($m_logfilename, "a");
    $text = date("Y-m-d H:i:s")." $s\n";
    fwrite($flog, $text);
    fclose($flog);
}

function diecode($code, $msg)
{
	print "$msg\n";
	exit($code);
}

reset($m_backup_dir);

if ($m_verb)
{
    /*output header*/
    echo "$m_name $m_version\n";
    /*output target db*/
    echo "target: $m_db@$m_host\n";
}

?>
