copy /Y .\S30\S07Z.hex .\Upgrade\S07Z.hex

rem 软件版本
set sw_version=V1.0.1

cd .\Upgrade

rem 获取时间
set date_str=%date:~0,4%%date:~5,2%%date:~8,2%_%time:~0,2%%time:~3,2%%time:~6,2%

firmware.exe S07Z.bin v01.00.00.00 S07Z_MC_%sw_version%_%date_str%.bin
mergehex.exe -m boot.hex S07Z.hex -o S07Z_MC_%sw_version%_%date_str%.hex