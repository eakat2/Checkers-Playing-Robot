clear all; close all; clc;

L1 = 9.746;
L2 = 23.5;
L3 = 18.475;
L4 = 9;
phi = 90;

x = 30;
y = 0;
z = -9;


%Theta 1
th1 = atan2d(y,x);

%Theta 3
A = x - L4*cosd(th1)*cosd(phi);
B = y - L4*sind(th1)*cosd(phi);
C = z - L1 - L4*sind(phi);
th3 = acosd((A^2+B^2+C^2-L2^2-L3^2)/(2*L2*L3));

%Theta 2
a = L3*sind(th3);
b = L2 + L3*cosd(th3);
c = z - L1 - L4*sind(phi);
r = sqrt(a^2+b^2);
th2_1 = atan2d(c,sqrt(r^2-c^2))-atan2d(a,b);
th2_2 = atan2d(c,-sqrt(r^2-c^2))-atan2d(a,b);

%Theta 4
th4_1 = phi - th2_1 - th3;
th4_2 = phi - th2_2 - th3;