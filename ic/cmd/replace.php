<?
/*
    replace.php <файл> <строка1> <строка2>
	Замещение в файле <файл> всех строк <строка1> на строку <строка2>
*/

if ($argc != 4)
{
	print "Неверное число аргументов.\n";
	exit(1);
}

$filename = $argv[1];
$str1     = $argv[2];
$str2     = $argv[3];


if (!$fp = fopen($filename, 'r'))
{
    print "Не удалось открыть для чтения файл $filename\n";
    exit(2);
}

$content = fread ($fp, filesize($filename));
fclose ($fp);

$replaced = str_replace($str1, $str2, $content);

if (!$fp = fopen($filename, 'w'))
{
    print "Не удалось открыть для записи файл $filename\n";
    exit(3);
}

$writed_bytes = fwrite ($fp, $replaced);
if (!$writed_bytes)
{
    print "Ошибка записи в файл $filename\n";
    exit(4);
}
	
fclose ($fp);

?>