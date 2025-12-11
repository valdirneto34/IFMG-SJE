DELIMITER //
CREATE PROCEDURE sp_gerar_mensalidades(IN p_matricula_id INT)
BEGIN
    DECLARE v_duracao_meses INT;
    DECLARE v_valor_total DECIMAL(10, 2);
    DECLARE v_valor_parcela DECIMAL(10, 2);
    DECLARE v_data_matricula DATE;
    DECLARE v_contador INT DEFAULT 1;
    DECLARE v_data_vencimento DATE;
    DECLARE v_curso_id INT;

-- 1. Obter dados da Matrícula e do Curso
SELECT m.data_matricula, m.valor_total_curso, c.duracao_meses, m.turma_id
INTO v_data_matricula, v_valor_total, v_duracao_meses, v_curso_id
FROM matriculas m JOIN turmas t ON m.turma_id = t.turma_id
JOIN cursos c ON t.curso_id = c.curso_id WHERE m.matricula_id = p_matricula_id;

-- 2. Condição de Validação (Duração do Curso)
IF v_duracao_meses IS NULL OR v_duracao_meses <= 0 THEN SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Curso não possui duração válida para geração de mensalidades.';
ELSE SET v_valor_parcela = v_valor_total / v_duracao_meses;
WHILE v_contador <= v_duracao_meses DO
SET v_data_vencimento = DATE_ADD(v_data_matricula, INTERVAL v_contador MONTH);
SET v_data_vencimento = CONCAT(YEAR(v_data_vencimento), '-', MONTH(v_data_vencimento), '-10');

INSERT INTO mensalidades (matricula_id, numero_parcela, data_vencimento, valor_nominal, status_pag)
VALUES (p_matricula_id, v_contador, v_data_vencimento, v_valor_parcela,'Pendente');

SET v_contador = v_contador + 1;
END WHILE;
END IF;
END //
DELIMITER ;
/*
Decisões de Implementação:
Tratamento de Validação (NULL/Zero): A cláusula IF inicial verifica se a duração do curso (v_duracao_meses) é NULL ou menor ou igual a zero. 
Essa validação garante que a procedure não tente realizar uma divisão por zero (v_valor_total / v_duracao_meses) e evita a geração de parcelas inválidas, abortando a operação com um erro (SIGNAL SQLSTATE).
Cálculo de Data de Vencimento: A data de vencimento é calculada dinamicamente utilizando o comando DATE_ADD(..., INTERVAL v_contador MONTH) em conjunto com a data de matrícula (v_data_matricula). 
Para forçar o vencimento sempre para o dia 10, usa-se a função CONCAT(YEAR(...), '-', MONTH(...), '-10'), garantindo consistência na política de cobrança mensal.
Eficiência de Loop (WHILE): Utiliza-se a estrutura de repetição WHILE para iterar de 1 até a duração total do curso (v_duracao_meses). 
O comando INSERT é executado dentro do loop, criando todas as parcelas de forma sequencial e automática em uma única execução da procedure.
Status Inicial Padrão: Todas as parcelas são inseridas com status_pag='Pendente'. Isso estabelece o estado financeiro inicial correto e diferencia as parcelas que ainda serão devidas.
*/

-- Preparação (garantindo que Aluno e Matrícula existam)
INSERT INTO pessoas (pessoa_id, nome, data_nasc, cpf, email) VALUES
(120, 'Aluno Teste Gerar', '2000-01-01', '12012012000', 'teste@gerar.com');
INSERT INTO alunos (aluno_id, nivel_proeficiencia_inicial) VALUES (120, 'Básico');
INSERT INTO matriculas (matricula_id, aluno_id, turma_id, data_matricula, valor_total_curso, status_mat) VALUES
(50, 120, 11, '2025-11-20', 900.00, 'Ativa'); -- Turma ID 11 (Curso 9: Italiano Rápido, 3 meses)

-- --------------------------------------------------
/*
TESTE DE SUCESSO (CENÁRIO POSITIVO)
A matrícula ID 50 (fictícia) no curso 'Italiano Rápido' (3 meses, valor 900.00) 
será processada.
A procedure deve inserir 3 parcelas de 300.00 com status 'Pendente'.
O vencimento deve ser o dia 10 dos meses subsequentes (10/12/2025, 10/01/2026, 10/02/2026).
*/
CALL sp_gerar_mensalidades(50);

-- Verificação (Deve retornar 3 linhas, todas com status 'Pendente')
SELECT numero_parcela, data_vencimento, valor_nominal, status_pag FROM mensalidades WHERE matricula_id = 50;

--- Preparação (garantindo que Aluno exista para não falhar na FK matriculas_alunos)
INSERT INTO pessoas (pessoa_id, nome, data_nasc, cpf, email) VALUES
(121, 'Aluno Teste Falha', '2000-01-01', '12112112100', 'teste@falha.com');
INSERT INTO alunos (aluno_id, nivel_proeficiencia_inicial) VALUES (121, 'Básico');

--- --------------------------------------------------
/*
TESTE DE FALHA (CENÁRIO NEGATIVO - Matrícula Inexistente)
O teste chama a procedure com uma Matrícula ID 999 que não existe no banco de dados. 
O SELECT INTO dentro da procedure não encontrará registros e retornará NULL para a 
variável v_duracao_meses.
O procedimento deve ser bloqueado pela cláusula IF (v_duracao_meses IS NULL) e 
retornar o erro 'Curso não possui duração válida para geração de mensalidades.'
O retorno esperado é o erro SQLSTATE 45000.
*/
-- ESTE COMANDO DEVE GERAR O ERRO: 'Curso não possui duração válida para geração de mensalidades.'
CALL sp_gerar_mensalidades(999);

-- Verificação (Deve retornar 0 linhas)
SELECT * FROM mensalidades WHERE matricula_id = 999;

DELIMITER //
CREATE PROCEDURE sp_aplicar_desconto(IN p_matricula_id INT, IN p_percentual_desconto DECIMAL(5, 2))
BEGIN
    DECLARE v_fator_multiplicador DECIMAL(10, 6);

IF p_percentual_desconto IS NULL OR p_percentual_desconto <= 0 OR p_percentual_desconto > 100 THEN 
SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Percentual de desconto inválido (deve ser entre 0.01 e 100.00). Operação abortada.';
ELSE SET v_fator_multiplicador = 1 - (p_percentual_desconto / 100);
UPDATE mensalidades SET valor_nominal = valor_nominal * v_fator_multiplicador
WHERE matricula_id = p_matricula_id AND status_pag = 'Pendente';

SELECT ROW_COUNT() AS parcelas_atualizadas;
END IF;
END //
DELIMITER ;
/*
Decisões de Implementação:
Validação de Percentual: A cláusula IF inicial impõe regras de negócio rigorosas para o percentual de desconto (p_percentual_desconto). Ela impede que descontos sejam nulos, negativos ou maiores que 100%. 
A falha nessa condição dispara um SIGNAL SQLSTATE, abortando a operação antes de qualquer alteração nos dados financeiros.
Aplicação Seletiva (status_pag = 'Pendente'): A atualização do valor nominal (UPDATE mensalidades) é filtrada de forma restritiva pela condição status_pag = 'Pendente'. 
Esta decisão é crucial para a integridade contábil, pois impede a alteração de parcelas que já foram pagas ('Pago') ou que já foram identificadas como dívida consolidada ('Vencido').
Cálculo com Fator Multiplicador: Em vez de subtrair o valor do desconto (valor_nominal - (valor_nominal * p_percentual_desconto / 100)), o cálculo utiliza o fator multiplicador (1 - p_percentual_desconto / 100). 
Isso simplifica a expressão do UPDATE (valor_nominal * v_fator_multiplicador), tornando o código mais limpo e menos propenso a erros de precedência matemática.
Feedback de Operação (ROW_COUNT): O comando SELECT ROW_COUNT() AS parcelas_atualizadas é utilizado para retornar ao chamador (o usuário ou a aplicação) o número exato de linhas que foram afetadas pelo UPDATE. 
Isso oferece um feedback claro e auditável sobre o resultado da operação de desconto.
*/

/*
TESTE DE SUCESSO (CENÁRIO POSITIVO)

A Matrícula ID 2 tem 8 parcelas pendentes de 300.00. 
Aplicaremos um desconto de 10% (Multiplicador = 0.90).
O valor nominal deve ser atualizado de 300.00 para 270.00 (300.00 * 0.90).
O retorno esperado é uma tabela com o valor 8 (o número de parcelas atualizadas).
*/
CALL sp_aplicar_desconto(2, 10.00);

-- Verificação 1: Confirma o número de linhas atualizadas
-- Retornará 'parcelas_atualizadas' = 8
-- Verificação 2: Confirma que os valores foram atualizados para 270.00
SELECT matricula_id, numero_parcela, valor_nominal, status_pag FROM mensalidades WHERE matricula_id = 2;

/*
TESTE DE FALHA (CENÁRIO NEGATIVO)
Tentativa de aplicar um desconto de 120% (Inválido). 
O procedimento deve ser bloqueado pela cláusula IF inicial e retornar o erro 'Percentual de desconto inválido...'.
O retorno esperado é o erro SQLSTATE 45000 e 0 linhas afetadas.
*/
-- ESTE COMANDO DEVE GERAR O ERRO: 'Percentual de desconto inválido (deve ser entre 0.01 e 100.00). Operação abortada.'
CALL sp_aplicar_desconto(2, 120.00);

-- Verificação (Confirma que NENHUMA parcela foi atualizada, permanecendo 270.00)
SELECT matricula_id, numero_parcela, valor_nominal, status_pag FROM mensalidades WHERE matricula_id = 2;



-- call sp_gerar_mensalidades(1);

-- delete from mensalidades where matricula_id = 1;

-- select * from mensalidades where matricula_id = 1;

-- call sp_aplicar_desconto(1, 10.00);
-- call sp_aplicar_desconto(1, 150.00);

/*													PROCEDURES POSTGRE SQL
CREATE OR REPLACE PROCEDURE escola_idiomas.sp_gerar_mensalidades(
    p_matricula_id INT
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_duracao_meses INT;
    v_valor_total DECIMAL(10, 2);
    v_data_matricula DATE;
    v_valor_parcela DECIMAL(10, 2);
    v_contador INT := 1;
    v_data_vencimento DATE;
BEGIN
    -- 1. Obter dados da Matrícula e do Curso
    SELECT
        m.data_matricula,
        m.valor_total_curso,
        c.duracao_meses
    INTO
        v_data_matricula,
        v_valor_total,
        v_duracao_meses
    FROM
        escola_idiomas.matriculas m
    JOIN
        escola_idiomas.turmas t ON m.turma_id = t.turma_id
    JOIN
        escola_idiomas.cursos c ON t.curso_id = c.curso_id
    WHERE
        m.matricula_id = p_matricula_id;

    -- 2. Condição de Validação (Duração do Curso)
    IF v_duracao_meses IS NULL OR v_duracao_meses <= 0 THEN
        RAISE EXCEPTION 'Curso não possui duração válida para geração de mensalidades.';
    ELSE
        -- 3. Calcular valor da parcela (assumindo parcelas iguais)
        v_valor_parcela := v_valor_total / v_duracao_meses;

        -- 4. Loop para Inserir Parcelas
        WHILE v_contador <= v_duracao_meses LOOP
            -- Calcula a data de vencimento: dia 10 do mês (data_matricula + contador meses).
            v_data_vencimento := (v_data_matricula + (v_contador || ' month')::interval);
            v_data_vencimento := DATE_TRUNC('month', v_data_vencimento) + INTERVAL '9 days'; -- Define o dia 10

            INSERT INTO escola_idiomas.mensalidades (
                matricula_id,
                numero_parcela,
                data_vencimento,
                valor_nominal,
                status_pag
            )
            VALUES (
                p_matricula_id,
                v_contador,
                v_data_vencimento,
                v_valor_parcela,
                'Pendente'
            );

            v_contador := v_contador + 1;
        END LOOP;
    END IF;
END;
$$;
*/

/* CREATE OR REPLACE PROCEDURE escola_idiomas.sp_aplicar_desconto(
    p_matricula_id INT,
    p_percentual_desconto DECIMAL
)
LANGUAGE plpgsql
AS $$
DECLARE
    v_fator_multiplicador DECIMAL;
    v_linhas_afetadas INT;
BEGIN
    -- 1. Verificação de Segurança (Percentual de Desconto)
    IF p_percentual_desconto IS NULL OR p_percentual_desconto <= 0 OR p_percentual_desconto > 100 THEN
        RAISE EXCEPTION 'Percentual de desconto inválido (deve ser entre 0.01 e 100.00). Operação abortada.';
    ELSE
        -- 2. Calcular Fator Multiplicador (Ex: 10% -> 0.90)
        v_fator_multiplicador := 1 - (p_percentual_desconto / 100);

        -- 3. Atualizar (UPDATE) o valor nominal das mensalidades pendentes
        UPDATE escola_idiomas.mensalidades
        SET
            valor_nominal = valor_nominal * v_fator_multiplicador
        WHERE
            matricula_id = p_matricula_id
            AND status_pag = 'Pendente';

        -- Captura o número de linhas afetadas para feedback (opcional)
        GET DIAGNOSTICS v_linhas_afetadas = ROW_COUNT;
        RAISE NOTICE 'Total de % parcelas pendentes atualizadas com desconto de %%%', v_linhas_afetadas, p_percentual_desconto;
    END IF;
END;
$$; 
*/


