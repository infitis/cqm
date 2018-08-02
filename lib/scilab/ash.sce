//----------------------------------------------
global a b c _f _a err alg

//----------------------------------------------
function y=ash(F)
y = a*F^2 + b*F + c
endfunction

//----------------------------------------------
function cur()
global a b c
printf("a = %f, b = %f, c = %f\n", a,b,c);
endfunction

//----------------------------------------------
function inpfa()
global _f _a
_f = input("F values formatted as [F1 F2 ...] ");
_a = input("A values formatted as [A1 A2 ...] ");
if length(_f) <> length(_a) then error("length(F) <> length(A)!");end;
endfunction

//----------------------------------------------
function outfa()
cur();
printf("error is %1.10f\n", err);
Fv = -b/(2*a);
Av = c-(b^2)/(4*a);
printf("vertex is F=%f, A=%f\n", Fv, Av);
g(_f(1)*0.66, _f(length(_f))*1.33);
plot2d(_f, _a, -4);
endfunction

//----------------------------------------------
function an = mylinsolve(X, Y)
detX  = det(X);
detXi = [0 0 0];

for i=1:1:length(X(1,:)),
Xi = X; Xi(:,i)=Y;
detXi(i) = det(Xi);
end;

for i=1:1:length(X(1,:)),
an(i) = detXi(i)/detX;
end;

endfunction

//----------------------------------------------
function abcq()
global a b c _f _a err
inpfa();

sx=0; sx2=0; sx3=0; sx4=0; sy=0; sxy=0; sx2y=0;
for i=1:1:length(_f),
sx  = sx  + _f(i);
sx2 = sx2 + _f(i)^2;
sx3 = sx3 + _f(i)^3;
sx4 = sx4 + _f(i)^4;
sy  = sy  + _a(i);
sxy = sxy + _f(i)*_a(i);
sx2y= sx2y+ (_f(i)^2)*_a(i);
end;
qa = [sx4 sx3 sx2; sx3 sx2 sx; sx2 sx length(_f)];
qb = [sx2y sxy sy]';
//[qq,kerA]=linsolve(qa,qb);
qq=mylinsolve(qa,qb);
a=qq(1);
b=qq(2);
c=qq(3);

err = sum((ash(_f)-_a)^2);

outfa();
endfunction

//----------------------------------------------
function abci()
global a b c _f _a err alg
inpfa();

if alg == '' then alg = 'nd'; end;
//make matrix
fu=[_f;_a];
//define error function
deff("[e]=G(s,z)","e=z(2)-s(1)-s(2)*z(1)-s(3)*z(1)^2");
//initial parameters
a0=[0.01;0.1;100];
[aa,err]=datafit(G,fu,a0,alg);
c=aa(1);
b=aa(2);
a=aa(3);

outfa();
endfunction

//----------------------------------------------
function new(aa,bb,cc)
global a b c
a = aa;
b = bb;
c = cc;
endfunction

//----------------------------------------------
function y=f(A)
global a b c
D = b^2 - 4*a*(c-A);
if D<0 then error("D<0");
else
y = (-b-sqrt(D))/(2*a);end;
endfunction

//----------------------------------------------
function g(Fmin, Fmax)
//xbasc();
x = Fmin:((Fmax-Fmin)/50):Fmax;
fplot2d(x,ash);
xgrid(5);
endfunction

//----------------------------------------------
function salg(newalg)
global alg
alg = newalg;
endfunction

//----------------------------------------------
function h()
printf("\n --- Coal Quality Monitoring. Methodologist Help ---\n");
printf("new(a, b, c)  - set new a, b, c values\n");
printf("cur           - print current a, b, c values\n");
printf("abcq          - square-least calculation new a, b, c by F and A sets\n");
printf("abci          - datafit func calculation new a, b, c by F and A sets\n");
printf("salg(alg)     - set algorythm for abci qn or gc or nd (default)\n");
printf("ash(F)        - calculation ash value by F\n");
printf("f(A)          - calculation F by A\n");
printf("g(Fmin, Fmax) - build graphic y=ash(F)\n");
printf("h             - print this help\n");
endfunction

//----------------------------------------------
alg='';
h;

//----------------------------------------------

