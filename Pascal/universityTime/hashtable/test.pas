program test;
uses hashTableLibrary;

var h: hashtable;
   i: integer;

begin
   htinit(h);
   for i:=2*n downto 0 do
	htadd(h,i);
   htoutput(h);
   htdelone(h,0); htdelone(h,10);
   htoutput(h);
   htfill(h);
   htoutput(h);
   writeln; write('#power of ht = ',htpower(h)); writeln;
   //write('is it in ht? ',htinhashtable(h,5),'   ');
   
   htfree(h);
   
end.