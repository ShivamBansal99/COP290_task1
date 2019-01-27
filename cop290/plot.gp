set style fill solid 0.25 border -1
set style boxplot outliers pointtype 7
set style data boxplot
set xlabel "Matrix size"
set ylabel "time(microsec)"
set yrange [0:600]
set title 'time vs Size' font 'Arial,14';
set xtics ('mkl' 1, 'openblas' 2)
plot for [i=1:2] '75x3.bat' using (i):i notitle
pause -1
