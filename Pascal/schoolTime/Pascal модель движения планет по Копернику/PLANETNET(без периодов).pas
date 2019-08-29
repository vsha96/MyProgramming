program alibaba;
uses GRAPHABC;

var
  m, g, r1, r2, r3, r4, r5, r6, r7, r8, r9, w1, w2, w3, w4, w5, w6, w7, w8, w9: double;
  x0, y0, i, px1, px2, px3, px4, px5, px6, px7, px8, px9, py1, py2, py3, py4, py5, py6, py7, py8, py9,k,a,x,y: integer;
  mx, my, t, dt, x1, x2, x3, x4, x5, x6, x7, x8, x9, y1, y2, y3, y4, y5, y6, y7, y8, y9: real;
  time:string;
  got,tp:real;
  
begin
setpencolor(clblack);

  
  t := 0;

  
  g := 6.667429;
  m := 1.99;
  
  r1 := 57.9;
  r2 := 108.2;
  r3 := 149.5;
  r4 := 227.9;
  
  r5 := 778.3;
  r6 := 1428;
  r7 := 2872;
  r8 := 4498;
  r9 := 5910;
  
  writeln('Введите 0 - 4 планеты');
  write('Введите 1 - все планеты');
  readln(k);
  
  x0 := windowwidth div 2;
  y0 := windowheight div 2;
  
  if k=0 then begin
  my := windowheight / (2 * r4 + 10);
  end
  else begin
  my := windowheight / (2 * r9 + 10);
  end;
  
  mx := my;
  got:=6.28/(sqrt(g * M / r3) / r3);
  
  sleep(5);
  t:=0;
  
if k=0 then begin
  dt := 50;
  for i := 0 to 100000000 do 
  begin
    lockdrawing;
    clearwindow;
    
    floodfill(1,1,clBlack);
    
    setpencolor(clBlack); 
    
    w1 := sqrt(g * M / r1) / r1;
    x1 := r1 * cos(w1 * t);
    y1 := r1 * sin(w1 * t);
    
    w2 := sqrt(g * M / r2) / r2;
    x2 := r2 * cos(w2 * t);
    y2 := r2 * sin(w2 * t);
    
    w3 := sqrt(g * M / r3) / r3;
    x3 := r3 * cos(w3 * t);
    y3 := r3 * sin(w3 * t);
    
    w4 := sqrt(g * M / r4) / r4;
    x4 := r4 * cos(w4 * t);
    y4 := r4 * sin(w4 * t);
    
    for a := 0 to 500 do 
          begin
            x := random(1000);
            y := random(1000);
            putpixel(x, y, clWhite);
          end;
    
    px1 := round(x1 * mx) + x0;
    py1 := y0 - round(y1 * my);
    Circle(px1, py1, 3);
    floodfill(px1, py1, clRed);
    
    px2 := round(x2 * mx) + x0;
    py2 := y0 - round(y2 * my);
    Circle(px2, py2, 5);
    floodfill(px2, py2,  clGoldenrod);
    
    px3 := round(x3 * mx) + x0;
    py3 := y0 - round(y3 * my);
    Circle(px3, py3, 6);
    floodfill(px3, py3, clBlue);
    
    px4 := round(x4 * mx) + x0;
    py4 := y0 - round(y4 * my);
    Circle(px4, py4, 8);
    floodfill(px4, py4, clRed);
    
    setpencolor(clYellow);
    Circle(x0, y0, 40);
    floodfill(x0, y0, clYellow);
   
    sleep(5);
    t := t + dt;
    
    str(t/got,time);
    
    textout(10,10,time);
    textout(5,0+30,'Периоды обращения:');
    textout(5,15+30,'Меркурий 0.26');
    textout(5,30+30,'Венера 0.61');
    textout(5,45+30,'Земля 1');
    textout(5,60+30,'Марс 2');
    redraw;
  end;
  end
  else begin
    dt := 1000;
    for i := 0 to 100000000 do 
    begin
    lockdrawing;
    clearwindow;
    
    floodfill(1,1,clBlack);
    
    setpencolor(clBlack); 
    
    w5 := sqrt(g * M / r5) / r5;
    x5 := r5 * cos(w5 * t);
    y5 := r5 * sin(w5 * t);
    
    w6 := sqrt(g * M / r6) / r6;
    x6 := r6 * cos(w6 * t);
    y6 := r6 * sin(w6 * t);
    
    w7 := sqrt(g * M / r7) / r7;
    x7 := r7 * cos(w7 * t);
    y7 := r7 * sin(w7 * t);
    
    w8 := sqrt(g * M / r8) / r8;
    x8 := r8 * cos(w8 * t);
    y8 := r8 * sin(w8 * t);
    
    w9 := sqrt(g * M / r9) / r9;
    x9 := r9 * cos(w9 * t);
    y9 := r9 * sin(w9 * t);
    
    for a := 0 to 500 do 
          begin
            x := random(1000);
            y := random(1000);
            putpixel(x, y, clWhite);
          end;
    
    px5 := round(x5 * mx) + x0;
    py5 := y0 - round(y5 * my);
    Circle(px5, py5, 7);
    floodfill(px5, py5, clRed);
    
    px6 := round(x6 * mx) + x0;
    py6 := y0 - round(y6 * my);
    Circle(px6, py6, 5);
    floodfill(px6, py6, rgb(204,204,0));
    
    px7 := round(x7 * mx) + x0;
    py7 := y0 - round(y7 * my);
    Circle(px7, py7, 4);
    floodfill(px7, py7, rgb(0,0,200));
    
    px8 := round(x8 * mx) + x0;
    py8 := y0 - round(y8 * my);
    Circle(px8, py8, 3);
    floodfill(px8, py8, rgb(0,0,255));
  
    px9 := round(x9 * mx) + x0;
    py9 := y0 - round(y9 * my);
    Circle(px9, py9, 2);
    floodfill(px9, py9, rgb(128,128,128));
    
    setpencolor(clYellow);
    Circle(x0, y0, 22);
    floodfill(x0, y0, clYellow);
   
    sleep(5);
    t := t + dt;
    
    str(t/got,time);
    textout(10,10,time);
    
    textout(5,0+30,'Периоды обращения:');
    textout(5,15+30,'Юпитер 12');
    textout(5,30+30,'Сатурн 29');
    textout(5,45+30,'Уран 85');
    textout(5,60+30,'Нептун 164');
    textout(5,75+30,'Плутон 248');
    
    redraw;
    end;
  end;
  
end.