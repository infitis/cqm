<?
/*
    replace.php <䠩�> <��ப�1> <��ப�2>
	����饭�� � 䠩�� <䠩�> ��� ��ப <��ப�1> �� ��ப� <��ப�2>
*/

if ($argc != 4)
{
	print "����୮� �᫮ ��㬥�⮢.\n";
	exit(1);
}

$filename = $argv[1];
$str1     = $argv[2];
$str2     = $argv[3];


if (!$fp = fopen($filename, 'r'))
{
    print "�� 㤠���� ������ ��� �⥭�� 䠩� $filename\n";
    exit(2);
}

$content = fread ($fp, filesize($filename));
fclose ($fp);

$replaced = str_replace($str1, $str2, $content);

if (!$fp = fopen($filename, 'w'))
{
    print "�� 㤠���� ������ ��� ����� 䠩� $filename\n";
    exit(3);
}

$writed_bytes = fwrite ($fp, $replaced);
if (!$writed_bytes)
{
    print "�訡�� ����� � 䠩� $filename\n";
    exit(4);
}
	
fclose ($fp);

?>