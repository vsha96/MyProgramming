unit vectors;
interface
	const n = 3;
	type vector = array[1..n] of integer;
	    type matrix = array[1..n, 1..n] of integer;
	procedure Swap(var a: vector; i,j:integer);
	    procedure SwapM(var m: matrix; i,j,q,p: integer);
	procedure VectorRead(var a: vector);
	    procedure MatrixRead(var m: matrix);
	procedure VectorWrite(var a: vector);
	    procedure MatrixWrite(var m: matrix);
	function VectorPowOf2(var a: vector): integer;
	function VectorFullSqr(var a: vector): integer;
	function VectorFib(var a: vector): integer;
	procedure VectorSortSelect(var a: vector);
	procedure VectorSortBubble(var a: vector);
	procedure VectorSortInsert(var a: vector);
	{error}//procedure VectorSortBInsert(var a: vector);
{---MATRIX---}
	procedure MatrixT(var m: matrix);
	function MatrixSumLn(var m: matrix; i:integer): integer;
	function MatrixCountNullCl(var m: matrix): integer;
	procedure MatrixSaddlePoints(var m: matrix);

implementation
	procedure Swap(var a:vector; i,j:integer);
		var t: integer;
		begin t:=a[j]; a[j]:=a[i]; a[i]:=t; end;
	procedure SwapM(var m: matrix; i,j,q,p: integer);
	    var t: integer;
	    begin t:=m[i,j]; m[i,j]:=m[q,p]; m[q,p]:=t; end;
	procedure VectorRead(var a: vector);
		var i: integer;
		begin 
			writeln('Input array which size ',n,': ');
			for i:=1 to n do 
				read(a[i]);
		end;
	procedure MatrixRead(var m: matrix);
		var i,j: integer;
		begin
			writeln('Input matrix which size ',n,'*',n);
			for i:=1 to n do
				for j:=1 to n do
					read(m[i,j]);
		end;
	procedure VectorWrite(var a: vector);
		var i: integer;
		begin 
			for i:=1 to n do
			begin
				write(' a[',i,']=', a[i],' ');
				writeln;
			end;
		end;
	procedure MatrixWrite(var m: matrix);
		var i,j: integer;
		begin 
			for i:=1 to n do
			begin
				for j:=1 to n do
				begin
					write({' m[',i,',',j,']=',} m[i,j]:4,' ' {,' '});
				end;
				writeln;
			end;
		end;
	function VectorPowOf2(var a: vector): integer;
	var i,t,k: integer;
	begin
		k:=0;
		for i:=1 to n do 
		begin
			t:=1;
			while t < a[i] do
				t:=t*2;
			if t = a[i] then k:=k+1;
		end;
		vectorpowof2:=k;
	end;
	function vectorfullsqr(var a: vector): integer;
	var i,t,k: integer;
	begin
		k:=0;
		for i:=1 to n do 
		begin
			t:=1;
			while t*t < a[i] do
			        t:=t+1;
			if t*t = a[i] then k:=k+1;
		end;
		vectorfullsqr:=k;
	end;
	function vectorfib(var a: vector): integer;
	var i,f1,f2,t,k: integer;
	begin
		k:=0;
		for i:=1 to n do
		begin
			f1:=1; f2:=1;
			while f2 < a[i] do
			begin
				t:=f2; f2:=f2+f1; f1:=t;
			end;
			if f2 = a[i] then k:=k+1;
		end;
		vectorfib:=k;
	end;
	//some sorts
	procedure VectorSortSelect(var a: vector);
		var i,j,posmax: integer;
		    c,k: integer;
		begin
			c:=0; k:=0;
			for i:=n downto 2 do
			begin
				posmax:=1;
				for j:=2 to i do
				begin
					c:=c+1;
					if a[posmax]<a[j] then 
					begin
						posmax:=j;
					end;
				end;
				if i<>posmax then begin swap(a,i,posmax); k:=k+1; end;
			end;
			writeln('<VSortSelect>Comparisons= ',c,'; Transpositions= ',k,'</VSortSelect>');
		end;
	procedure vectorsortbubble(var a: vector);
		var i,j: integer;
		    c,k: integer;
		begin
			c:=0; k:=0;
			for i:=n downto 2 do
				for j:=1 to i-1 do 
				begin
					c:=c+1;
					if a[j]>a[j+1] then begin swap(a,j,j+1); k:=k+1; end;
				end;
			writeln('<VSortBubble>Comparisons= ',c,'; Transpositions= ',k,'</VSortBubble>');
		end;
	procedure vectorsortinsert(var a: vector);
		var i,j: integer;
		    c,k: integer;
		begin
			c:=0; k:=0;
			for i:=2 to n do
			begin
				j:=i-1;
				c:=c+1;
				while (j>0) and (a[j]>a[j+1]) do
				begin
					swap(a,j,j+1); k:=k+1;
					j:=j-1;
				end;
			end;
			writeln('<VSortInsert>Comparisons= ',c,'; Transpositions= ',k,'</VSortInsert>');
		end;
	{error
	procedure VectorSortBInsert(var a: vector);
		var i,e: integer;
		    left,mid,right: integer;
		    c,k: integer;
		begin
			c:=0; k:=0;
			for i:=2 to n do
			begin
				left:=1; right:=i-1; mid:= (right-left) div 2;
				while left < right do
				begin
					mid:= (right-left) div 2;
					c:=c+1;
					if a[mid] < a[i] then
					begin
						left:=mid+1;
					end
					else begin
						right:=mid-1;
					end;
				end;
				for e:=i-1 downto mid do
				begin
					swap(a,e,e+1); k:=k+1;
				end;
			end;
			writeln('<VSortBInsert>Comparisons= ',c,'; Transpositions= ',k,'</VSortBInsert>');
		end;
	}
	procedure MatrixT(var m: matrix);
	    var i,j: integer;
	    begin
		for j:=1 to n do
		    for i:=1 to j do
			SwapM(m,i,j,j,i);
	    end;
	function MatrixSumLn(var m: matrix; i: integer): integer;
	    var j: integer;
		s: integer;
	    begin
		s:=0;
		for j:=1 to n do
		    s:=s+m[i,j];
		MatrixSumLn:=s;
	    end;
	function MatrixCountNullCl(var m: matrix): integer;
	    var i,j: integer;
		c: integer;
		b: boolean;
	    begin
		b:=true; c:=0;
		for j:=1 to n do
		    begin
			for i:=1 to n do
			    if m[i,j]<>0 then
				begin
				    b:=false; break;
				end;
			if b=true then c:=c+1;
			b:=true;
		    end;
		matrixcountnullcl:=c;
	    end;
	procedure MatrixSaddlePoints(var m: matrix);
	    var i,j,q: integer;
		max,min: integer; b: boolean;
	    begin
		b:=true;
		for i:=1 to n do
		    for j:=1 to n do
			begin
			    max:=m[i,j];
			    min:=m[i,j];
			    for q:=1 to n do
				begin
//writeln('if (',i,',',j,')<(',i,',',q,')',' and ','min>(',q,',',j,')');
				    if (max < m[i,q]) or (min > m[q,j]) then
					begin b:=false; break; end;
				end;
			    if b then write(' (',i,',',j,') ');
			    b:=true;
			end;
	    end;
end.






