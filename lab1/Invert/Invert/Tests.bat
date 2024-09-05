@echo off

SET PROGRAM="%~1"

REM ���� ��� ���������� ����������
echo Test 1.1
%PROGRAM% > nul && goto err

REM ���� ��� ���������� ���������� ����������
echo Test 1.2
%PROGRAM% "matrix.txt" "long" > nul && goto err

REM ���� � ������� ��������
echo Test 2
%PROGRAM% "matrix.txt" || goto err

REM ���� ������� � ������������� = 0
echo Test 3
%PROGRAM% "matrix1.txt" || goto 

REM ���� ������� � ����������� ���������� ���������
echo Test 4
%PROGRAM% "matrix2.txt" && goto err

REM ���� ������� � ������������� ����������
echo Test 5
%PROGRAM% "matrix3.txt" && goto err

echo Success!
exit 0

:err
echo Program failed
exit 1