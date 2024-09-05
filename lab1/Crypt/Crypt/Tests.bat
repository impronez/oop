@echo off

SET PROGRAM="%~1"

REM ���� ��� ���������� ����������
echo Test 1.1
%PROGRAM% > nul && goto err

REM ���� ��� 1 ���������: �����
echo Test 1.2
%PROGRAM% "crypt" > nul && goto err

REM ���� ��� 2� ����������: �����, ������� ����
echo Test 1.3
%PROGRAM% "crypt" "test-data\Replace.exe" > nul && goto err

REM ���� ��� 3-� ����������: �����, ������� � �������� �����
echo Test 1.4
%PROGRAM% "crypt" "test-data\Replace.exe" "test-data\Replace1.exe" > nul && goto err

REM ���� ��� 5 ����������: �����, ������� � �������� �����, ���� ���������� � ������ ��������
echo Test 1.5
%PROGRAM% "crypt" "test-data\Replace.exe" "test-data\Replace1.exe" 100 sd > nul && goto err

REM ���� ��� ������������ ������ ���������
echo Test 1.6
%PROGRAM% "fcrypt" "test-data\Replace.exe" "test-data\Replace1.exe" 100 > nul && goto err

REM ���� ��� ����� < 0
echo Test 1.7
%PROGRAM% "crypt" "test-data\Replace.exe" "test-data\Replace1.exe" -1 > nul && goto err

REM ���� ��� ����� > 255
echo Test 1.8
%PROGRAM% "crypt" "test-data\Replace.exe" "test-data\Replace1.exe" 256 > nul && goto err

REM ���������� �����
echo Test 3
%PROGRAM% "crypt" "test-data\Replace.exe" "test-data\Replace1.exe" 100 || goto err
fc.exe "test-data\Replace.exe" "test-data\Replace1.exe" > nul && goto err

REM ������������ ����������� �����
echo Test 4
%PROGRAM% "decrypt" "test-data\Replace1.exe" "test-data\Replace2.exe" 100 || goto err
fc.exe "test-data\Replace.exe" "test-data\Replace2.exe" > nul || goto err

echo Success!
exit 0

:err
echo Program failed
exit 1