uses GraphABC;
var
  i :integer;
begin
//окно,крыша,основа
  Rectangle(100,100,200,200);
  rectangle (130,130,170,170);
  Line(150,130,150,170);
  line(130,150,170,150);
  line(100,100,150,80);
  line(150,80,200,100);
  
//забор
  line(200,200,300,200);
  line(300,200,300,180);
  
  for i:=0 to 4 do begin
    line(300-i*20,180,290-i*20,160);
    line(290-i*20,160,280-i*20,180);
  end;
  
  for i:=0 to 4 do begin
    line(300-i*20,180,300-i*20,200);
  end;

//солнышко =зззззззз
  SetPenColor(clBlack);
  circle(400,50,30);
  
//дерево
  rectangle(500,200,510,160);
  
  setpenwidth(30);
  setpencolor(clmoneygreen);
  circle(490,138,15);
  
  setpenwidth(30);
  setpencolor(clmoneygreen);
  circle(520,130,15);
  
  setpenwidth(30);
  setpencolor(clmoneygreen);
  circle(506,110,15);
  
  setpenwidth(2);
  
//дымоход
  line(200,100,200,80);
  line(200,80,190,80);
  line(190,80,190,95);
  
//горизонт
  line(0,200,640,200);
  
//-------------------------------------------------
//ЗАЛИВКА
  
  //house
  Floodfill(102,102,clgray);
  
  //glass
  floodfill(155,155,clskyblue);
  floodfill(145,145,clskyblue);
  floodfill(145,155,clskyblue);
  floodfill(155,145,clskyblue);
  
  //roof
  floodfill(150,90,clmaroon);
  
  //chimney
  floodfill(195,85,clsilver);
  
  //fence
  for i:=0 to 4 do begin
    floodfill(295-i*20,185,clbrown);
  end;
  
  //earth
  floodfill(400,400,clgreen);
  
  //sun
  floodfill(400,50,clyellow);
  
  //tree
  floodfill(505,195,clbrown);
  

end.