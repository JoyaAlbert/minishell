#!/bin/bash
make
# Script completo de testing para pipelining - Versión consolidada
# Incluye todos los tests de test_pipeline.sh y simple_test.sh
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

PASSED=0
FAILED=0
TOTAL=0

test_pipeline() {
    local desc="$1"
    local cmd="$2"
    local category="$3"
    
    echo -e "${BLUE}[$category] $desc${NC}"
    echo "  Command: $cmd"
    
    # Ejecutar en bash
    bash_result=$(bash -c "$cmd" 2>/dev/null)
    
    # Ejecutar en minishell, filtrar prompts y líneas vacías
    mini_output=$(echo "$cmd" | ./minishell 2>/dev/null)
    mini_result=$(echo "$mini_output" | grep -v "サ »" | sed '/^$/d' | sed 's/\x0//g')
    
    # Normalizar espacios en blanco
    bash_normalized=$(echo "$bash_result" | sed 's/[[:space:]]*$//')
    mini_normalized=$(echo "$mini_result" | sed 's/[[:space:]]*$//')
    
    echo "  Bash:      '$bash_normalized'"
    echo "  Minishell: '$mini_normalized'"
    
    if [ "$bash_normalized" = "$mini_normalized" ]; then
        echo -e "  ${GREEN}✓ PASSED${NC}"
        ((PASSED++))
    else
        echo -e "  ${RED}✗ FAILED${NC}"
        # Mostrar más detalles para debugging
        echo "  Bash lines: $(echo "$bash_result" | wc -l)"
        echo "  Mini lines: $(echo "$mini_result" | wc -l)"
        ((FAILED++))
    fi
    
    ((TOTAL++))
    echo ""
}

# Preparar archivos de test
echo "Preparando archivos de test..."
printf "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n" > numbers.txt
printf "apple\nbanana\ncherry\ndate\negg\nfig\ngrape\nhoney\n" > words.txt
printf "line1\nline2\nline3\nline4\nline5\n" > simple.txt
printf "line1\nline2\nline3\nline4\nline5\nline6\nline7\nline8\nline9\nline10\n" > test_lines.txt
printf "apple\nbanana\ncherry\ndate\neggplant\nfig\ngrape\nhoney\nice\njam\n" > test_words.txt
seq 1 20 > test_numbers.txt

echo -e "\n${YELLOW}=== TESTS BÁSICOS ===${NC}\n"

# Tests básicos con 1 pipe
test_pipeline "Contar archivos" "ls | wc -l" "1-PIPE"
test_pipeline "Primeras 5 líneas y contar" "cat numbers.txt | head -5 | wc -l" "1-PIPE"
test_pipeline "Últimas 3 líneas y contar" "cat numbers.txt | tail -3 | wc -l" "1-PIPE"
test_pipeline "Echo simple pipe" "echo 'hello world test' | wc -w" "1-PIPE"

echo -e "${YELLOW}=== TESTS CON 2 PIPES ===${NC}\n"

# Tests con 2 pipes
test_pipeline "Head -> Tail -> Count" "cat numbers.txt | head -8 | tail -5 | wc -l" "2-PIPES"
test_pipeline "Numbers -> Head -> Tail -> Count" "cat numbers.txt | head -6 | tail -3 | wc -l" "2-PIPES"
test_pipeline "Head 5 and count" "cat test_numbers.txt | head -5 | wc -l" "2-PIPES"
test_pipeline "2 pipes: head->tail->count" "cat test_numbers.txt | head -8 | tail -3 | wc -l" "2-PIPES"
test_pipeline "Archivos -> Head -> Count" "ls | head -10 | wc -l" "2-PIPES"
test_pipeline "Numbers -> Head -> Tail" "cat test_numbers.txt | head -10 | tail -5 | wc -l" "2-PIPES"

echo -e "${YELLOW}=== TESTS CON 3 PIPES ===${NC}\n"

# Tests con 3 pipes
test_pipeline "3 pipes: head->tail->head->count" "cat test_numbers.txt | head -8 | tail -6 | head -3 | wc -l" "3-PIPES"
test_pipeline "4 Pipes: Head->Tail->Head->Count" "cat numbers.txt | head -8 | tail -6 | head -4 | wc -l" "3-PIPES"
test_pipeline "4 Pipes: Words test" "cat words.txt | head -6 | tail -4 | head -2 | wc -l" "3-PIPES"
test_pipeline "Head->Tail->Head->Count" "cat test_lines.txt | head -8 | tail -6 | head -3 | wc -l" "3-PIPES"
test_pipeline "Numbers complex" "cat test_numbers.txt | head -15 | tail -10 | head -5 | wc -l" "3-PIPES"
test_pipeline "Words test" "cat test_words.txt | head -8 | tail -6 | head -3 | wc -l" "3-PIPES"

echo -e "${YELLOW}=== TESTS CON 4 PIPES ===${NC}\n"
# Tests con 4 pipes
test_pipeline "4 pipes complex" "cat test_numbers.txt | head -15 | tail -12 | head -8 | tail -4 | wc -l" "4-PIPES"
test_pipeline "Lines 4 pipes" "cat test_lines.txt | head -9 | tail -7 | head -5 | tail -2 | wc -l" "4-PIPES"

echo -e "${YELLOW}=== TESTS CON 5+ PIPES ===${NC}\n"
# Tests con 5 pipes
test_pipeline "5 pipes complex" "cat test_numbers.txt | head -18 | tail -15 | head -12 | tail -8 | head -5 | wc -l" "5-PIPES"
test_pipeline "5 pipes words" "cat test_words.txt | head -8 | tail -6 | head -4 | tail -3 | head -2 | wc -l" "5-PIPES"

# Tests con 6 pipes
test_pipeline "6 pipes ultimate" "cat test_numbers.txt | head -20 | tail -18 | head -15 | tail -12 | head -8 | tail -5 | wc -l" "6-PIPES"

echo -e "${YELLOW}=== TESTS CON REDIRECCIONES ===${NC}\n"

# Test helper function for redirection tests that need file verification
test_redirection_with_file_check() {
    local desc="$1"
    local write_cmd="$2"
    local read_cmd="$3"
    local category="$4"
    
    echo -e "${BLUE}[$category] $desc${NC}"
    echo "  Write: $write_cmd"
    echo "  Read: $read_cmd"
    
    # Test bash
    bash -c "$write_cmd" 2>/dev/null
    bash_result=$(bash -c "$read_cmd" 2>/dev/null)
    
    # Test minishell
    echo "$write_cmd" | ./minishell 2>/dev/null >/dev/null
    mini_output=$(echo "$read_cmd" | ./minishell 2>/dev/null)
    mini_result=$(echo "$mini_output" | grep -v "サ »" | sed '/^$/d' | sed 's/\x0//g')
    
    # Normalizar espacios en blanco
    bash_normalized=$(echo "$bash_result" | sed 's/[[:space:]]*$//')
    mini_normalized=$(echo "$mini_result" | sed 's/[[:space:]]*$//')
    
    echo "  Bash:      '$bash_normalized'"
    echo "  Minishell: '$mini_normalized'"
    
    if [ "$bash_normalized" = "$mini_normalized" ]; then
        echo -e "  ${GREEN}✓ PASSED${NC}"
        ((PASSED++))
    else
        echo -e "  ${RED}✗ FAILED${NC}"
        echo "  Bash lines: $(echo "$bash_result" | wc -l)"
        echo "  Mini lines: $(echo "$mini_result" | wc -l)"
        ((FAILED++))
    fi
    
    ((TOTAL++))
    echo ""
}

# Tests con redirecciones de salida simples
test_redirection_with_file_check "Redirect output to file" "echo 'test output' > output_test.txt" "cat output_test.txt" "REDIRECT"

# Test de pipe con redirección (solo la parte de escritura, luego verificamos)
test_redirection_with_file_check "Pipe with redirect" "cat test_numbers.txt | head -3 > temp_output.txt" "cat temp_output.txt | wc -l" "REDIRECT"

# Test append en dos pasos
echo -e "${BLUE}[REDIRECT] Append redirect (two steps)${NC}"
echo "  Step 1: echo 'line1' > append_test.txt"
echo "  Step 2: echo 'line2' >> append_test.txt"
echo "  Read: cat append_test.txt | wc -l"

# Bash test
bash -c "echo 'line1' > append_test.txt" 2>/dev/null
bash -c "echo 'line2' >> append_test.txt" 2>/dev/null
bash_result=$(bash -c "cat append_test.txt | wc -l" 2>/dev/null)

# Minishell test
echo "echo 'line1' > append_test.txt" | ./minishell 2>/dev/null >/dev/null
echo "echo 'line2' >> append_test.txt" | ./minishell 2>/dev/null >/dev/null
mini_output=$(echo "cat append_test.txt | wc -l" | ./minishell 2>/dev/null)
mini_result=$(echo "$mini_output" | grep -v "サ »" | sed '/^$/d' | sed 's/\x0//g')

bash_normalized=$(echo "$bash_result" | sed 's/[[:space:]]*$//')
mini_normalized=$(echo "$mini_result" | sed 's/[[:space:]]*$//')

echo "  Bash:      '$bash_normalized'"
echo "  Minishell: '$mini_normalized'"

if [ "$bash_normalized" = "$mini_normalized" ]; then
    echo -e "  ${GREEN}✓ PASSED${NC}"
    ((PASSED++))
else
    echo -e "  ${RED}✗ FAILED${NC}"
    echo "  Bash lines: $(echo "$bash_result" | wc -l)"
    echo "  Mini lines: $(echo "$mini_result" | wc -l)"
    ((FAILED++))
fi

((TOTAL++))
echo ""

# Tests con redirecciones de entrada
test_pipeline "Input redirect" "wc -l < test_numbers.txt" "REDIRECT"
test_pipeline "Complex redirect" "head -5 < test_numbers.txt | tail -3 | wc -l" "REDIRECT"

echo -e "${YELLOW}=== TESTS CON HEREDOC ===${NC}\n"

# Test helper function for heredoc tests
test_heredoc() {
    local desc="$1"
    local cmd="$2"
    local input_lines="$3"
    local category="$4"
    
    echo -e "${BLUE}[$category] $desc${NC}"
    echo "  Command: $cmd"
    echo "  Input lines: $input_lines"
    
    # Test bash
    bash_result=$(echo -e "$input_lines" | bash -c "$cmd" 2>/dev/null)
    
    # Test minishell - note: heredoc may need interactive input simulation
    # For now, let's test what we can
    echo "  Bash result: '$bash_result'"
    echo "  Minishell: [HEREDOC test - requires interactive input]"
    echo -e "  ${YELLOW}⚠ SKIPPED (requires interactive testing)${NC}"
    
    ((TOTAL++))
    echo ""
}

# Example heredoc tests (commented for now since they need interactive input)
# test_heredoc "Simple heredoc count" "wc -l << EOF" "line1\nline2\nline3\nEOF" "HEREDOC"
# test_heredoc "Cat heredoc" "cat << END" "Hello\nWorld\nEND" "HEREDOC"

echo -e "${BLUE}[HEREDOC] Manual test instructions:${NC}"
echo "  To test heredoc manually, run:"
echo "  ./minishell"
echo "  Then type: wc -l << EOF"
echo "  Then type some lines and end with: EOF"
echo ""

echo -e "${YELLOW}=== RESUMEN FINAL ===${NC}"
echo -e "📊 Total tests ejecutados: $TOTAL"
echo -e "${GREEN}✓ Tests pasados: $PASSED${NC}"
echo -e "${RED}✗ Tests fallidos: $FAILED${NC}"

# Limpieza de archivos temporales
rm -f numbers.txt words.txt simple.txt test_lines.txt test_words.txt test_numbers.txt
rm -f output_test.txt temp_output.txt append_test.txt

if [ $FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ¡TODOS LOS TESTS PASARON EXITOSAMENTE!${NC}"
    exit 0
else
    echo -e "\n${RED}😞 Algunos tests fallaron. Revisar la implementación.${NC}"
    exit 1
fi
