@echo off

set PROGRAM="%~1"
REM TODO: �������� ��� 1, 2, 3, 5... ����������
REM TODO ���� �� ������� ����
REM �������� ��� ����������, � 1-�, 2-��, 3-��, 5-�
echo Test 1 
%PROGRAM% > nul && goto err

echo Test 1.1
%PROGRAM% "test-data\test1.txt" > nul && goto err

echo Test 1.2
%PROGRAM% "test-data\test1.txt" "%TEMP%\output0.txt" > nul && goto err

echo Test 1.3
%PROGRAM% "test-data\test1.txt" "%TEMP%\output0.txt" "dog" > nul && goto err

echo Test 1.4
%PROGRAM% "test-data\test1.txt" "%TEMP%\output0.txt" "dog" "lol" "text.txt" > nul && goto err

REM ���� � �������
echo Test 2
%PROGRAM% "test-data\test1.txt" "%TEMP%\output1.txt" 1231234 123 || goto err
fc "test-data\test1.txt" "%TEMP%\output1.txt" && goto err

REM �������� �� ������������
echo Test 3
%PROGRAM% "test-data\test2.txt" "%TEMP%\output2.txt" ma mama || goto err
fc "test-data\test2.txt" "%TEMP%\output2.txt" && goto err

REM �������� ��� ������� ������� ������
echo Test 4
%PROGRAM% "test-data\test2.txt" "%TEMP%\output3.txt" "" mama || goto err
fc "test-data\test2.txt" "%TEMP%\output3.txt" || goto err

REM �������� ��� ������ �� ������� ������
echo Test 5
%PROGRAM% "test-data\test2.txt" "%TEMP%\output4.txt" ma "" || goto err
fc "test-data\test2.txt" "%TEMP%\output4.txt" && goto err

REM �������� ��� ������� ������� � ���������� �������
echo Test 6
%PROGRAM% "test-data\test2.txt" "%TEMP%\output5.txt" "" "" || goto err
fc "test-data\test2.txt" "%TEMP%\output5.txt" || goto err

REM �������� ��� ������� �����
echo Test 7 
%PROGRAM% "test-data\large.txt" "%TEMP%\output6.txt" "hello" "lol" || goto err
fc "test-data\large.txt" "%TEMP%\output6.txt" > nul && goto err


echo Success!
exit 0

:err
echo Program failed
exit 1