#!/bin/bash

# ==========================================
# Configurações do Script
# ==========================================
ARQUIVO_CPP="main.cpp"           # Nome do seu arquivo fonte C++
EXECUTAVEL="./tp2_exec"         # Nome do executável a ser gerado
PASTA_ENTRADAS="entradas"       # Pasta onde estão os arquivos .txt de entrada
PASTA_SAIDAS="saidas"           # Pasta onde as saídas do seu programa serão salvas

# ==========================================
# Compilação
# ==========================================
echo "=> Compilando $ARQUIVO_CPP..."
# Compilando com otimização -O3 (recomendado para competições/trabalhos com tempo limite)
g++ -Wall -O3 "$ARQUIVO_CPP" -o "$EXECUTAVEL"

if [ $? -ne 0 ]; then
    echo "Erro de compilação. Abortando o teste."
    exit 1
fi

echo "=> Compilação concluída com sucesso!"
echo "------------------------------------------------"

# Cria a pasta de saídas caso ela não exista
mkdir -p "$PASTA_SAIDAS"

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
    arquivo_saida="$PASTA_SAIDAS/saida_$nome_base"

    echo -n "Testando $nome_base... "

    # O comando 'timeout' interrompe o programa se ele passar de 1 segundo
    timeout 1s $EXECUTAVEL < "$arquivo_entrada" > "$arquivo_saida"
    
    STATUS=$?

    if [ $STATUS -eq 124 ]; then
        echo "[FALHA] Tempo Limite Excedido (> 1 segundo)!"
    elif [ $STATUS -ne 0 ]; then
        echo "[FALHA] Erro de execução (Crash/Falha de Segmentação)!"
    else
        echo "[OK] Saída gerada em $arquivo_saida"
    fi
done

echo "------------------------------------------------"
echo "=> Testes finalizados!"