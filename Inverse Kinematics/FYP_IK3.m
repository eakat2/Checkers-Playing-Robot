clc; clear all; close all; 

L1 = 9.626;
L2 = 23.5;
L3 = 18.475;
L4 = 9;
phi = deg2rad(90);

x = 15;
y = 0;
z = 5;

%Theta 1
th1 = atan2(y,x);

%Theta 3
c3 = (x^2+y^2+(z-L1)^2-L2^2-L3^2)/(2*L2*L3);
s3_1 = sqrt(1-cos(c3)^2);
s3_2 = -sqrt(1-cos(c3)^2);
th3_1 = atan2(s3_1,c3);
th3_2 = atan2(s3_2,c3);
th3 = [th3_1 th3_2];

%Theta 2
c2_1 = (x/cos(th1)*(-L2-L3*cos(th3_1))+(z-L1)*L3*sin(th3_1))/(-L2^2-L3^2-2*L2*L3*cos(th3_1));
c2_2 = (x/cos(th1)*(-L2-L3*cos(th3_2))+(z-L1)*L3*sin(th3_2))/(-L2^2-L3^2-2*L2*L3*cos(th3_2));
s2_1_1 = sqrt(1-c2_1^2);
s2_1_2 = -sqrt(1-c2_1^2);
s2_2_1 = sqrt(1-c2_2^2);
s2_2_2 = -sqrt(1-c2_2^2);
th2_1_1 = atan2(s2_1_1,c2_1);
th2_1_2 = atan2(s2_1_2,c2_1);
th2_2_1 = atan2(s2_2_1,c2_2);
th2_2_2 = atan2(s2_2_2,c2_2);
th2 = [th2_1_1 th2_1_2 th2_2_1 th2_2_2];

%Theta 4
th4_1_1 = phi - th2_1_1 - th3_1;
th4_1_2 = phi - th2_1_2 - th3_1;
th4_2_1 = phi - th2_2_1 - th3_2;
th4_2_2 = phi - th2_2_2 - th3_2;
th4 = [th4_1_1 th4_1_2 th4_2_1 th4_2_2];

%Degrees
rad2deg(th1)
rad2deg(th2)
rad2deg(th3)
rad2deg(th4)
