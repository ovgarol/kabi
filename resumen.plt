set terminal png;
set output "grafica.png";
plot 'estats.d' u 1:2 w l t 'nacen', 'estats.d' u 1:3 w l t 'mueren', 'estats.d' u 1:4 w l t 'total', 'estats.d' u 1:5 w l t 'crecimiento';
exit;
