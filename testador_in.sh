#!/bin/bash

# ==========================================
# Configurações do Script
# ==========================================
ARQUIVO_CPP="main.cpp"           # Nome do seu arquivo fonte C++
EXECUTAVEL="./tp2_exec"         # Nome do executável a ser gerado
PASTA_ENTRADAS="entradas"       # Pasta onde estão os arquivos .txt de entrada

# ==========================================
# Compilação
# ==========================================
echo "=> Compilando $ARQUIVO_CPP..."
g++ -Wall -O3 "$ARQUIVO_CPP" -o "$EXECUTAVEL"

if [ $? -ne 0 ]; then
    echo "Erro de compilação. Abortando o teste."
    exit 1
fi

echo "=> Compilação concluída com sucesso!"
echo "------------------------------------------------"

# ==========================================
# Execução dos Casos de Teste
# ==========================================
# Verifica se a pasta de entradas tem arquivos .txt
if ! ls "$PASTA_ENTRADAS"/*.txt > /dev/null 2>&1; then
    echo "Nenhum arquivo .txt encontrado na pasta '$PASTA_ENTRADAS'."
    exit 1
fi

for arquivo_entrada in "$PASTA_ENTRADAS"/*.txt; do
    nome_base=$(basename "$arquivo_entrada")

    # Cabeçalho para separar visualmente os testes no terminal
    echo "====================================================="
    echo " EXECUTANDO: $nome_base"
    echo "====================================================="
    echo "-> [SAÍDA DO PROGRAMA]:"

    # Executa o programa jogando a saída direto no terminal
    timeout 1s $EXECUTAVEL < "$arquivo_entrada"
    
    STATUS=$?

    echo "-----------------------------------------------------"
    if [ $STATUS -eq 124 ]; then
        echo "[FALHA] Tempo Limite Excedido (> 1 segundo)!"
    elif [ $STATUS -ne 0 ]; then
        echo "[FALHA] Erro de execução (Crash/Falha de Segmentação)!"
    else
        echo "[OK] Executado com sucesso."
    fi
    echo "" # Linha em branco para o terminal respirar entre um teste e outro
done

echo "------------------------------------------------"
echo "=> Testes finalizados!"