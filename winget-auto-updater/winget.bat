@echo off
:: Verifica se ja esta rodando como Administrador
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo Elevando privilegios para Administrador...
    powershell -Command "Start-Process '%~f0' -Verb RunAs"
    exit /b
)

:: Executa a atualizacao completa sem prompts
echo Atualizando programas em segundo plano...
winget upgrade --all --silent --include-unknown --accept-source-agreements --accept-package-agreements

echo Tudo pronto! 
pause