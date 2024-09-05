@echo off

SET PROGRAM="%~1"

REM Тест при отсутствии аргументов
echo Test 1.1
%PROGRAM% > nul && goto err

REM Тест при 1 аргументе: режим
echo Test 1.2
%PROGRAM% "crypt" > nul && goto err

REM Тест при 2х аргументах: режим, входный файл
echo Test 1.3
%PROGRAM% "crypt" "test-data\Replace.exe" > nul && goto err

REM Тест при 3-х аргументах: режим, входной и выходной файлы
echo Test 1.4
%PROGRAM% "crypt" "test-data\Replace.exe" "test-data\Replace1.exe" > nul && goto err

REM Тест при 5 аргументах: режим, входной и выходной файлы, ключ шифрования и лишний аргумент
echo Test 1.5
%PROGRAM% "crypt" "test-data\Replace.exe" "test-data\Replace1.exe" 100 sd > nul && goto err

REM Тест при некорректном режиме программы
echo Test 1.6
%PROGRAM% "fcrypt" "test-data\Replace.exe" "test-data\Replace1.exe" 100 > nul && goto err

REM Тест при ключе < 0
echo Test 1.7
%PROGRAM% "crypt" "test-data\Replace.exe" "test-data\Replace1.exe" -1 > nul && goto err

REM Тест при ключе > 255
echo Test 1.8
%PROGRAM% "crypt" "test-data\Replace.exe" "test-data\Replace1.exe" 256 > nul && goto err

REM Шифрование файла
echo Test 3
%PROGRAM% "crypt" "test-data\Replace.exe" "test-data\Replace1.exe" 100 || goto err
fc.exe "test-data\Replace.exe" "test-data\Replace1.exe" > nul && goto err

REM Дешифрование предыдщуего файла
echo Test 4
%PROGRAM% "decrypt" "test-data\Replace1.exe" "test-data\Replace2.exe" 100 || goto err
fc.exe "test-data\Replace.exe" "test-data\Replace2.exe" > nul || goto err

echo Success!
exit 0

:err
echo Program failed
exit 1