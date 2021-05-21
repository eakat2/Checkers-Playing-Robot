L1 = 5.6;
L2 = 4.028;
L3 = 23.5;
L4 = 18.475;
L5 = 9;
phi = 90;

x = 10;
y = 0;
z = 2;

a = y;
b = -x;
c = L2;

% Theta 1

th1_1 = atan2d(b,a)+atan2d(sqrt(a^2+b^2-c^2),c);
th1_2 = atan2d(b,a)-atan2d(sqrt(a^2+b^2-c^2),c);

% Theta 2

K1 = cosd(th1_1)*x+sind(th1_1)*y;
d = L3^2-K1^2-L1^2-z^2-L4^2-L5^2+2*K1*L5*cosd(phi)+2*L1*L5*sind(phi)+2*L1*z-2*L5*sind(phi)*z;
e = 2*L4*L5*cosd(phi)-2*K1*L4;
f = 2*L4*z-2*L1*L4+2*L4*L5*sind(phi);

th23_1_1 = atan2d(f,e)+atan2d(sqrt(e^2+f^2-d^2),d);
th23_1_2 = atan2d(f,e)-atan2d(sqrt(e^2+f^2-d^2),d);

th2_1_1 = (K1-L4*cosd(th23_1_1)-L5*cosd(phi))/L3;
th2_1_2 = (K1-L4*cosd(th23_1_2)-L5*cosd(phi))/L3;

K1 = cos(th1_2)*x+sin(th1_2)*y;
d = L3^2-K1^2-L1^2-z^2-L4^2-L5^2+2*K1*L5*cos(phi)+2*L1*L5*sin(phi)+2*L1*z-2*L5*sin(phi)*z;
e = 2*L4*L5*cos(phi)-2*K1*L4;
f = 2*L4*z-2*L1*L4+2*L4*L5*sin(phi);

th23_2_1 = atan2d(f,e)+atan2d(sqrt(e^2+f^2-d^2),d);
th23_2_2 = atan2d(f,e)-atan2d(sqrt(e^2+f^2-d^2),d);

th2_2_1 = (K1-L4*cosd(th23_2_1)-L5*cosd(phi))/L3;
th2_2_2 = (K1-L4*cosd(th23_2_2)-L5*cosd(phi))/L3;

% Theta 3

th3_1_1 = th23_1_1 - th2_1_1;
th3_1_2 = th23_1_2 - th2_1_2;
th3_2_1 = th23_2_1 - th2_2_1;
th3_2_2 = th23_2_2 - th2_2_2;

% Theta 4

th4_1_1 = phi + th3_1_1 + th2_1_1;
th4_1_2 = phi + th3_1_2 + th2_1_2;
th4_2_1 = phi + th3_2_1 + th2_2_1;
th4_2_2 = phi + th3_2_2 + th2_2_2;



