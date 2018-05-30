<?php
/**
 * Created by PhpStorm.
 * User: Akmal Darari
 * Date: 30/05/2018
 * Time: 13.47
 */
$var1 = 20; //kalo int
$var4 = 5.4;
$var2 = "apa"; //kalo string
$var3 = array("apa", "apa", "apa");

if ($var4 == 5) {
    echo $var4;
} elseif ($var4 == 4) {
    die;
} else $var4 = 8 * 4;

for ($x = 0; $x <= 10; $x++) {
    echo "Hello world";
    static $y = 9;
}

$array = array($i, $a, $b);
foreach ($array as $value) {
    $var = $value['a'];
}

echo $value; //sama kayak printf
echo "Deddy" . $var . "senpai"; //sama kayak atas

$x = $y + $u;

function senpai($a)
{
    return $a - 15;
}

$a = $y / 5;
$b = $d / $a;

senpai($b);

while (true) {
    echo "Deddy senpaaai";
    break;
}
if (
$_GET
[
    'submit'
]
==
20
)
?>
