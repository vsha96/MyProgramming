program first;
uses vectors;
var m: matrix;
begin
	matrixread(m);
	//matrixt(m);
	matrixwrite(m);
	//writeln(matrixsumln(m,1));
	//writeln(matrixcountnullcl(m));
	matrixsaddlepoints(m);
end.