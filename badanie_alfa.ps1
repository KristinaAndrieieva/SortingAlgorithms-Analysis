$N = 25000
$I = 50

Write-Host "Shell Sort:"

.\SortingAlgorithms_Analysis.exe -b -a 6 -s 0 -t 0 -l $N -n $I -e 0 -r "alpha_shell.csv"
.\SortingAlgorithms_Analysis.exe -b -a 6 -s 0 -t 0 -l $N -n $I -e 1 -r "alpha_shell.csv"

Write-Host "Quick Sort:"
.\SortingAlgorithms_Analysis.exe -b -a 5 -s 0 -t 0 -l $N -n $I -p 0 -r "alpha_quick.csv"
.\SortingAlgorithms_Analysis.exe -b -a 5 -s 0 -t 0 -l $N -n $I -p 1 -r "alpha_quick.csv"
.\SortingAlgorithms_Analysis.exe -b -a 5 -s 0 -t 0 -l $N -n $I -p 2 -r "alpha_quick.csv"
.\SortingAlgorithms_Analysis.exe -b -a 5 -s 0 -t 0 -l $N -n $I -p 3 -r "alpha_quick.csv"

Write-Host "Wyniki w plikach CSV."