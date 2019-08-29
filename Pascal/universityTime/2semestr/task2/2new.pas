program gen; {we are searching min of function via genetic algorithm}
//uses strutils; FOR TESTING
const	eps = 1/16384; {epsilon}
	iterations = 100; {for stop condition}
	a = 0; b = 4; {segment}
	n = 9; {n+1 count of species in first creation}

type	FT = function(x:real):real;
	population = array[1..(n+1),1..2] of real; {representation of population}
	

var	iter {for iterations}: smallint;
	minprev,minpresent{UPD 13.05},minever{/UPD 13.05}: real; {for stop procedure, the best example from prev and present population}
	t: file of text; {presentation in test mode}
	pop: population; {population}
	i:integer;
	{FOR TESTING} {x1,x2:real;} iterwhile:integer;

function f(x:real):real;
	begin
		f:=(x-2.1)*(x-1.5)*(x-2.4)*(x-0.33)*(1-exp(x-3.5))*cos(x); {we want min of the function}
	end;

{вывод массива}
procedure showpop(pop: population);
	var	i:integer;
	begin
		writeln;
		writeln('===population===');
		write('x   ');
		for i:=1 to n+1 do
			begin
				write(' ',pop[i][1]:4:3,' ');
			end;
		writeln;
		write('f(x)');
		for i:=1 to n+1 do
			begin
				write(' ',pop[i][2]:4:3,' ');
			end;
		
		writeln;
	end;
{max в массиве}
function max(pop:population):real; {maximal value of target function}
	var i:integer;
	begin
		max:=pop[1][2];
		for i:=2 to n+1 do
			if pop[i][2]>max then max:=pop[i][2];
	end;
{min в массиве}
function min(pop:population):real; {minimal value of target function}
	var i:integer;
	begin
		min:=pop[1][2];
		for i:=2 to n+1 do
			if pop[i][2]<min then min:=pop[i][2];
	end;
{swap}
procedure swapsep(var a,b:byte);
	var t:byte;
	begin
		t:=a; a:=b; b:=t;
	end;

{1) генерация начальной популяции}
procedure god(var pop: population); {create n+1 species}
	var	x,d:real; i:integer;
	begin
		d:=(b-a)/n; x:=a;
		for i:=1 to n+1 do
			begin
				pop[i][1]:=x;
				x:=x+d;
			end;
		{I have test.pas for watching the population}
	end;

{2) оценка популяции, вычисление целевой функции для каждой особи}
procedure fx(f: FT; var pop: population);
	var	i:integer;
	begin
		for i:=1 to n+1 do
			pop[i][2]:=f(pop[i][1]);
	end;

{3) проверка критерия останова}
{критерий останова- выполнение алгоритмом априорно заданного числа итераций
без улучшения целевой функции}
function stop(iter:integer; minprev,minpresent:real):boolean;
	begin
		stop:=false;
		if (iter>iterations) and (abs(minprev-minpresent)<eps) then
			stop:=true;
	end;

{5) оператор скрещивания- двухточечное} {можно использовать smallint 16 бит - особь
представляем в виде 16 бит, в операторе мутации то же самое}
procedure cross(var individ1,individ2:real);
	var {FOR TESTING} {seq1,seq2: string[16];}
		gene1,gene2:integer; {gene in crossing}
		ex1,ex2:real; {individuals * x}
		sep1,sep2:byte; {separators}
	function gen(individ:real):integer; {for cutting a gen}
		begin
			gen:=((trunc(individ) div trunc(exp(sep1*ln(2))) mod trunc(exp((sep2-sep1)*ln(2)))))*trunc(exp(sep1*ln(2)))
		end;
	begin
		ex1:=individ1*2000; ex2:=individ2*2000; {2000 - this is good scaling for our segment}
			//seq1:=IntToBin(trunc(ex1),16);
			//seq2:=IntToBin(trunc(ex2),16);
		sep1:=random(16); sep2:=random(16); {random}
		if sep1>sep2 then swapsep(sep1,sep2);
			{//FOR TESTING}
			//writeln('sep1 ',sep1,' sep2 ',sep2);
			//writeln('seq1 ',seq1);
		gene1:=gen(ex1); gene2:=gen(ex2); {cut the gene from individ }
			//seq1:=IntToBin(trunc(ex1-gene1+gene2),16);
			//writeln('seq1 ',seq1,' new');
			//writeln('seq2 ',seq2);
			//seq2:=IntToBin(trunc(ex2-gene2+gene1),16);
			//writeln('seq2 ',seq2,' new');
		individ1:= (ex1-gene1+gene2)/2000; individ2:= (ex2-gene2+gene1)/2000;
	end;

{4) оператор селекции- схема пропорционального отбора}
procedure selection(var pop: population);
	type chance= array[1..n+1] of real;
		crosspop= array[1..n+1] of integer; {count of crossing for each individual}
	var average: real; {average value of func}
		chances: chance;
		c:real; {chance to gain a count of crossing}
		p1,p2: byte; {pointers to individuals}
		ex1,ex2: real; {two individuals under pointers}
		newpop: population;
			spop: crosspop;
			newbie: byte; {count of new individuals}
		i,m: integer;
		fmax: real; {for minimization}
	function spring(chances: chance):boolean;
		var i:integer;
		begin
			spring:=false;
			for i:=1 to n+1 do if chances[i]>0 then begin spring:=true; exit; end;
		end;
	function stillspring(spop: crosspop):boolean; {do we have count of crossing in pop?}
		var i:integer;
		begin
			stillspring:=false;
			for i:=1 to n+1 do if spop[i]>0 then begin stillspring:=true; exit; end;
		end;
	procedure initcrosspop(var spop: crosspop); {make zeros in counts of crossing for each individual}
		var i:integer;
		begin
			for i:=1 to n+1 do spop[i]:=0;
		end;
	{UPDATE 30.04.2019}
	procedure sendpop(pop1:population;var pop2:population); {after that pop2:=pop1}
		var i,j:integer;
		begin
			for i:=1 to n+1 do
				for j:=1 to 2 do
					begin
						pop2[i][j]:=pop1[i][j]
					end;
		end;
	{/UPDATE 30.04.2019}
	begin
		average:=0;
		for i:=1 to n+1 do average:=average+pop[i][2]/(n+1);
	{
	writeln;
	writeln('average ',average:4:5);
	}
		{подсчет вероятностей}
		fmax:=max(pop);
		for i:=1 to n+1 do begin chances[i]:=(-pop[i][2]+fmax+eps)/(-average+fmax+eps); {write(' ',chances[i]:4:5,' ');} end;
		average:=0;
		initcrosspop(spop);
		while spring(chances) do
			begin
				{now we are counting crossings}
				for i:=1 to n+1 do
					begin
					while chances[i]>0 do
						begin
							if chances[i]>=1 then
								begin
									chances[i]:=chances[i]-1;
									spop[i]:=spop[i]+1;
								end
							else
								begin
									c:=random(10000);
									if (c-chances[i]*10000<=0) then
										begin
											chances[i]:=chances[i]-1;
											spop[i]:=spop[i]+1;
										end
									else chances[i]:=chances[i]-1;
								end;
						end;
					end;
			end;
	{
	writeln;
	for i:=1 to n+1 do write('  spop  ',spop[i]);
	writeln;
	for i:=1 to n+1 do write(' chances ',chances[i]:3:3);
	writeln;
	}
		{теперь тыкаем и скрещиваем, если есть число скрещиваний для особи}
		{OLD}newbie:=0; {crossing дает +2 особи} m:=1; {counter for newpop}
		{UPDATE 30.04.2019}
		sendpop(pop,newpop);
		{/UPDATE 30.04.2019}
		while stillspring(spop) {and (newbie<10)} do
			begin
				p1:=random(n+2); p2:=random(n+2); {point to some individuals}
				ex1:=pop[p1][1]; ex2:=pop[p2][1];
													//writeln(p1,' ',p2,' ||');
													//write(' IAMHERE ');
													{
													writeln;
													for i:=1 to n+1 do
														write(spop[i],' ');
													writeln;
													}
				if (spop[p1]>0) and (spop[p2]>0) then
					begin
						cross(ex1,ex2);
						{UPDATE 30.04.2019}
						newpop[p1][1]:=ex1; newpop[p2][1]:=ex2;
						{/UPDATE 30.04.2019}
						{OLD}//newpop[m][1]:=ex1; newpop[m+1][1]:=ex2;
						{OLD}//newbie:=newbie+2; m:=m+2;
						spop[p1]:=spop[p1]-1;
						spop[p2]:=spop[p2]-1;
					end;
			end;
	{
	writeln;
	writeln('newpop');
	for i:=1 to n+1 do write(' ',newpop[i][1]:3:4);
	}
		{pop := newpop}
		for i:=1 to n+1 do pop[i][1]:=newpop[i][1];
		
	end;

{6) оператор мутации- перестановка случайно выбранных битов местами}
procedure mutation(var x:real);
	var b1,b2:byte;
		bit1,bit2:integer;
	function cutbit(individ:real;i:byte):integer; {for cutting the bit from value}
		begin
			cutbit:=((trunc(individ) div trunc(exp(i*ln(2))) mod 2));
		end;
	begin
		b1:=random(15); b2:=random(15);
		x:=x*8000;
		bit1:=cutbit(x,b1); bit2:=cutbit(x,b2); {cut the bit from value}
			{FOR TESTING}
			//writeln('MUTATION');
			//writeln('b1 ',b1,' b2 ',b2);
			//writeln('old x ',IntToBin(trunc(x),16));
		x:= (x+(bit2-bit1)*trunc(exp(b1*ln(2)))+(bit1-bit2)*trunc(exp(b2*ln(2))));
			//writeln('new x ',IntToBin(trunc(x),16));
		x:= x/8000;
			//writeln('new x ',x:4:5);
	end;


{7) вывод лучшего решения}

begin
	iter:=0;
	randomize;
	{main mode}
			god(pop); {create popilation} iter:=iter+1;
			fx(@f,pop);
			minpresent:=min(pop); {the best example in this population}
			minprev:=minpresent; {just for delete warning}
			{UPD 13.05}minever:=minpresent;{/UPD 13.05}
				{TESTING}
				{
				showpop(pop); 
				x1:=3.92; x2:=Pi;
				cross(x1,x2);
				mutation(x1);
				writeln('x1 = ',x1:4:5);
				}
				{need to turn on testing in procedure <mutation>}
				{/TESTING}
				{
				showpop(pop);
				selection(pop);
				showpop(pop);
				}
						//showpop(pop);
			
			while not stop(iter,minprev,minpresent) do
				begin
					iter:=iter+1;
					selection(pop);
					{mutation}
					for i:=1 to n+1 do
					begin
						mutation(pop[i][1]);
						{UPDATE 13.05}
						iterwhile:=0;
						while ((pop[i][1]<0) or (pop[i][1]>4)) and (iterwhile<=100) do 
						begin
							mutation(pop[i][1]); //if number jump out of segment after mutation
							iterwhile:=iterwhile+1;
						end;
						if (iterwhile>100) then pop[i][1]:=random(5);
						{/UPDATE 13.05}
					end;
					{/mutation}
					fx(@f,pop);
						//showpop(pop);
					minprev:=minpresent;
					minpresent:=min(pop);
				end;
			writeln;
			{UPD 13.05}
			if minever>minpresent then minever:=minpresent;
			{/UPD 13.05}
			writeln('target = -1.11208');
			writeln('minimum = ',minever:3:5);
			writeln;
	
	
end.