$exe = ".\projekt_algorytmy.exe"
$glowny_folder = "Wyniki_Koncowe"

$n_it = "50"
$p_opt = "3"
$e_opt = "1"
$rozmiar_z_A = "25000"

if (!(Test-Path $glowny_folder)) { New-Item -ItemType Directory $glowny_folder }

function Uruchom-Benchmark($subfolder, $plik, $cmd_args) {
    $path = "$glowny_folder\$subfolder"
    if (!(Test-Path $path)) { New-Item -ItemType Directory -Force -Path $path }
    $res_file = Join-Path $path $plik

    $arg_array = $cmd_args.Split(" ", [System.StringSplitOptions]::RemoveEmptyEntries)
    $arg_array += @("-n", $n_it, "-r", $res_file, "-b")

    Write-Host "Runner (n=$n_it) -> ${subfolder} | ${cmd_args}" -ForegroundColor Cyan

    & $exe $arg_array
}

Write-Host "`n BADANIE A (Skalowalnosc)" -ForegroundColor Yellow
$algorytmy = 4..6
$struktury = 0..2
$rozmiary = 10000, 25000, 50000, 100000

foreach ($a in $algorytmy) {
    foreach ($s in $struktury) {
        foreach ($l in $rozmiary) {
            $cmd = "-a $a -s $s -l $l -d 0 -t 0"
            if ($a -eq 5) { $cmd += " -p $p_opt" }
            if ($a -eq 6) { $cmd += " -e $e_opt" }
            Uruchom-Benchmark "Badanie_A" "wyniki_A.csv" $cmd
        }
    }
}


Write-Host "`n URUCHAMIAM BADANIE B (Rozkład danych)" -ForegroundColor Yellow
foreach ($s in 0..2) {
    foreach ($d in 0..3) {
        Uruchom-Benchmark "Badanie_B" "wyniki_B.csv" "-a 5 -s $s -p $p_opt -l $rozmiar_z_A -d $d -t 0"
    }
}


Write-Host "`nURUCHAMIAM BADANIE C (Typy danych)" -ForegroundColor Yellow
foreach ($t in 0, 1, 4, 5) {
    Uruchom-Benchmark "Badanie_C" "wyniki_C.csv" "-a 5 -s 0 -p $p_opt -l $rozmiar_z_A -d 0 -t $t"
}

Write-Host "`BADANIE OMEGA (Struktury)" -ForegroundColor Magenta
$struktury_omega = 0..5 | Where-Object { $_ -ne 3 }

foreach ($s in $struktury_omega) {
    Uruchom-Benchmark "Badanie_Omega" "wyniki_Omega.csv" "-a 5 -s $s -p $p_opt -l 10000 -d 0 -t 0"
}

Write-Host "`n--- WSZYSTKIE TESTY ZAKOŃCZONE ---" -ForegroundColor Green