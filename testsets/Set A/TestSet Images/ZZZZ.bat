setlocal EnableDelayedExpansion
echo switch (numberImage) >> output.txt
echo  { >> output.txt
set/A num=1

for /r %%f in (*) do (
	echo case !num!: >> output.txt
	echo currentImageFile = "%%~nxf"; >> output.txt
	echo break; >>output.txt
	set /a num+=1
)
echo default: >> output.txt
echo   currentImageFile = "child-1.png"; >> output.txt
echo  } >> output.txt
