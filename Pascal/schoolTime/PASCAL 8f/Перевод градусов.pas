program temperatura;
var
tk,tc,tf,tr,t: real;
n:integer;

begin
writeln('введите число: 1-из кельвина , 2- из цельсия , 3- фаренгейт , 4- реомюра ');
readln(n);
writeln('Введите кол-во градусов');
readln(t);

  case n of

    1:begin
    tc:=t-273.15;
    tf:=1.8*tc+32;
    tr:=tc/1.25;
    writeln(tc, ' цельсия ', tf, ' фарингейта ', tr, ' реомюра ');
    end;
    
    2:begin
    tk:=t+273.15;
    tf:=1.8*t+32;
    tr:=t/1.25;
    writeln(tk, ' кельвина ', tf, ' фарингейта ', tr, ' реомюра ');
    end;
    
    3:begin
    tc:=(t-32)/1.8;
    tk:=tc+273.15;
    tr:=tc/1.25;
    writeln(tc, ' цельсия ', tk, ' кельвина ', tr, ' реомюра ');
    end;
    
    4:begin
    tc:=t*1.25;
    tk:=tc+273.15;
    tf:=1.8*tc+32;
    writeln(tc, ' цельсия ', tk, ' кельвина ', tf, ' фаренгейта ');
    end

  end;
  
end.
