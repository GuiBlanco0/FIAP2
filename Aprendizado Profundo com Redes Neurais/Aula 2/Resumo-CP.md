# Resumo para Prova Prática — Redes Neurais / Bank Marketing

> Baseado em: Aula 03 (Preparação e Exploração de Dados) e Aula 04 (Fundamentos de Redes Neurais: Perceptron)

---

## 1. Conceitos básicos de dados

| Termo | Significado |
|---|---|
| **Amostra** | Uma linha da tabela (ex: um cliente) |
| **Feature** | Uma coluna de entrada (ex: `age`, `job`) |
| **Target (y)** | Variável que queremos prever (ex: `y = yes/no`) |
| **Variável numérica** | Valor contínuo/discreto (age, balance, day, campaign, pdays, previous) |
| **Variável categórica** | Texto/categoria (job, marital, education, housing, loan, contact, month, poutcome) |

**Ideia-chave:** uma rede neural só trabalha com números — categorias precisam ser transformadas antes de entrar no modelo.

### Dataset da disciplina: UCI Bank Marketing
- **Problema:** prever se o cliente vai contratar um depósito a prazo.
- **Entrada:** 16 features (dados do cliente + da campanha).
- **Saída:** `y = yes` ou `no`.
- Tamanho total: **45.211 linhas × 17 colunas**.

---

## 2. Análise Exploratória de Dados (EDA)

Perguntas a fazer sempre:
- Quantas amostras e features existem?
- Há dados ausentes?
- Existem categorias desconhecidas ("unknown")?
- Existem duplicatas?
- As classes estão desbalanceadas?
- Alguma coluna causa *data leakage*?

### Ferramentas do pandas
```python
df.shape                 # tamanho (linhas, colunas)
df.dtypes                # tipos de cada coluna
df.isna().sum()          # contagem de NaN por coluna
df.duplicated().sum()    # quantidade de linhas duplicadas
df.describe()            # estatísticas (min, max, média, mediana, desvio, percentis)
df['col'].value_counts() # contagem de categorias / classes
```

### Dados ausentes — dois tipos
- **Ausência explícita:** `NaN`, `NULL`, `None`, string vazia.
- **Ausência codificada:** `"unknown"`, `"not available"`, `999`, `-1`, etc.
  - No Bank Marketing, várias colunas categóricas têm o valor `"unknown"`.
  - Antes de tratar (remover/substituir), é preciso entender o **significado no contexto** do problema.

### Duplicatas
- Podem ser erro de coleta OU registros legítimos repetidos.
- Decisão depende do significado da linha no dataset — não remover sem pensar.

### Distribuição da classe alvo (desbalanceamento)
```
no  = 39.922 (~88,3%)
yes = 5.289  (~11,7%)
```
- **Atenção:** um modelo que sempre prevê "no" teria ~88% de acurácia, mas seria inútil (ignora a classe minoritária).
- Por isso, **acurácia sozinha pode enganar** — usar precisão, recall, F1 e matriz de confusão (assunto de aula futura).

### Data Leakage
- Ocorre quando o modelo recebe **informação que não existiria no momento real da previsão**.
- **Exemplo real no dataset:** a coluna `duration` (duração da ligação) só é conhecida DEPOIS da ligação acontecer.
  - **Regra:** remover `duration` antes de treinar um modelo preditivo real.

---

## 3. Divisão dos dados: Train / Validation / Test

| Conjunto | Função | Proporção usual |
|---|---|---|
| **Train** | Aprende os parâmetros do modelo | 70% |
| **Validation** | Apoia decisões durante o desenvolvimento | 15% |
| **Test** | Avaliação final, dados independentes | 15% |

### Estratificação (`stratify=y`)
- Preserva a proporção das classes (ex: ~88%/12%) em cada conjunto.
- Sem isso, o Val/Test pode ficar mais desbalanceado por acaso.

```python
from sklearn.model_selection import train_test_split

X_train, X_temp, y_train, y_temp = train_test_split(
    X, y, test_size=0.30, random_state=42, stratify=y
)
X_val, X_test, y_val, y_test = train_test_split(
    X_temp, y_temp, test_size=0.50, random_state=42, stratify=y_temp
)
```

### Regra fundamental (evitar vazamento na preparação)
- **Primeiro separar os dados; depois aprender transformações (normalização, encoding) usando SOMENTE o Train.**
- Certo: `preprocess.fit(X_train)` → `preprocess.transform(X_val/X_test)`
- Errado: calcular média/desvio/categorias usando Train + Val + Test juntos.
- **O Test nunca deve influenciar nenhuma decisão** de preparação ou modelagem — só é usado no final.

### Pipeline completo (Aula 03)
```
Carregar → Explorar (EDA) → Identificar problemas → Remover leakage → Dividir (split) → Salvar CSVs
```
Saída: `bank_train.csv`, `bank_validation.csv`, `bank_test.csv` (reutilizados nas aulas seguintes).

```python
X_model = X.drop(columns=['duration'])   # remove leakage
y_model = y.map({'no': 0, 'yes': 1})      # target vira 0/1

train = X_train.copy(); train['y'] = y_train
train.to_csv('bank_train.csv', index=False)
# idem para validation e test
```

---

## 4. O Perceptron

### O que é
A unidade básica de uma rede neural: **soma ponderada + ativação**.

```
Entradas (x1, x2, x3) → pesos (w1, w2, w3) → soma z → ativação φ(z) → saída ŷ
```

### Fórmulas principais
- **Soma ponderada:** `z = x1*w1 + x2*w2 + x3*w3 + b`
- **Ativação degrau:** `ŷ = 1 se z ≥ 0, senão ŷ = 0`
- **Erro:** `erro = y - ŷ`
- **Atualização dos pesos:** `wi ← wi + η * erro * xi`
- **Atualização do bias:** `b ← b + η * erro`
- **η (eta)** = taxa de aprendizado — controla o tamanho da correção a cada erro.

### Como o perceptron aprende (passo a passo)
1. Recebe `x`
2. Calcula `z`
3. Gera `ŷ` (aplica ativação)
4. Compara `ŷ` com `y` → calcula erro
5. Atualiza pesos e bias (só muda se erro ≠ 0)

Uma passagem completa por todas as amostras = **1 época**.

### Exemplo manual (memorizar a lógica, não decorar números)
Dataset didático (5 amostras, 3 features):
| Amostra | x1 | x2 | x3 | y |
|---|---|---|---|---|
| A1 | 1 | 0 | 1 | 1 |
| A2 | 0 | 1 | 1 | 0 |
| A3 | 1 | 1 | 0 | 1 |
| A4 | 0 | 0 | 1 | 0 |
| A5 | 1 | 1 | 1 | 1 |

Inicialização: `w = [0.20, -0.30, 0.10]`, `b = -0.05`, `η = 0.10`

- Quando `erro = 0` → pesos **não mudam**.
- Quando `erro ≠ 0` → pesos das entradas ativas (x=1) são corrigidos (aumentam se erro=+1, diminuem se erro=-1).
- Pesos finais após a época: `w = [0.30, -0.20, 0.00]`, `b = -0.05`.

### Algoritmo genérico (pseudo-código / numpy)
```python
w = np.zeros(n_features)
b = 0

for epoca in range(n_epocas):
    for x_i, y_i in dados:
        z = np.dot(x_i, w) + b
        y_pred = 1 if z >= 0 else 0
        erro = y_i - y_pred
        w = w + lr * erro * x_i
        b = b + lr * erro
```

### Limitações do perceptron
- Só separa classes com uma **fronteira linear**.
- Se a relação entre as variáveis for não linear, um único perceptron pode falhar.
- Solução futura: **camadas ocultas** + funções de ativação não lineares (redes neurais multicamadas).

---

## 5. Pré-processamento para o Perceptron

### Por que transformar categorias em números?
O perceptron faz multiplicações e somas — não existe `"management" × 0.35`. É preciso converter texto em número.

### One-Hot Encoding
Cada categoria vira uma coluna binária (0 ou 1), sem impor ordem artificial entre categorias.

| job original | job_management | job_student | job_technician |
|---|---|---|---|
| management | 1 | 0 | 0 |
| technician | 0 | 0 | 1 |
| student | 0 | 1 | 0 |

### Escalonamento (StandardScaler)
Variáveis numéricas em escalas muito diferentes (ex: `age` em dezenas vs `balance` em milhares) podem dominar a soma ponderada `z`.

`z_scaled = (x - média) / desvio_padrão`

### Regra contra vazamento no pré-processamento
- `fit` **somente** no Train.
- `transform` aplicado em Train, Validation e Test com os parâmetros aprendidos no Train.
- Categorias desconhecidas em Val/Test → usar `handle_unknown='ignore'` no OneHotEncoder.

```python
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder, StandardScaler

encoder = OneHotEncoder(handle_unknown='ignore', sparse_output=False)

preprocess = ColumnTransformer([
    ('num', StandardScaler(), numericas),
    ('cat', encoder, categoricas)
])

X_train_prep = preprocess.fit_transform(X_train)   # fit + transform
X_val_prep   = preprocess.transform(X_val)          # só transform
X_test_prep  = preprocess.transform(X_test)         # só transform
```

---

## 6. Treinando e avaliando o Perceptron (scikit-learn)

```python
from sklearn.linear_model import Perceptron
from sklearn.metrics import (
    accuracy_score, precision_score, recall_score,
    f1_score, confusion_matrix, classification_report
)

perceptron = Perceptron(max_iter=1000, eta0=0.1, random_state=42)
perceptron.fit(X_train_prep, y_train)

# Avaliação na validação
y_val_pred = perceptron.predict(X_val_prep)
print('Accuracy:', accuracy_score(y_val, y_val_pred))
print('Precision:', precision_score(y_val, y_val_pred, zero_division=0))
print('Recall:', recall_score(y_val, y_val_pred, zero_division=0))
print('F1:', f1_score(y_val, y_val_pred, zero_division=0))
print(classification_report(y_val, y_val_pred, zero_division=0))
print(confusion_matrix(y_val, y_val_pred))

# Teste final (só depois de fechar todas as decisões do modelo!)
y_test_pred = perceptron.predict(X_test_prep)
print(classification_report(y_test, y_test_pred, zero_division=0))
```

### Métricas — o que cada uma responde
| Métrica | Pergunta que responde |
|---|---|
| **Accuracy** | Quantos acertos no geral? |
| **Precision** | Dos previstos como 1, quantos realmente eram 1? |
| **Recall** | Dos verdadeiros 1, quantos o modelo encontrou? |
| **F1** | Equilíbrio entre precision e recall |

### Matriz de confusão
```
             Prevê 0   Prevê 1
Real 0         TN         FP
Real 1         FN         TP
```
- Pergunta-chave: o modelo está de fato encontrando a classe 1 (minoritária)?

### Regra de ouro do Test
- Usar o conjunto de Test **somente depois** de todas as decisões de modelagem estarem fechadas.
- Evita "espiar" a prova final e enviesar o ajuste do modelo.

---

## 7. Checklist rápido para a prova prática

1. [ ] Carregar dados e checar `shape`, `dtypes`.
2. [ ] Identificar colunas numéricas vs categóricas.
3. [ ] Checar `isna()`, `duplicated()`, categorias `"unknown"`.
4. [ ] Checar distribuição da classe alvo (desbalanceamento).
5. [ ] Identificar e remover colunas de **data leakage** (ex: `duration`).
6. [ ] Separar `X` e `y`; converter `y` para 0/1 se for texto.
7. [ ] Fazer split Train/Validation/Test com `stratify=y`.
8. [ ] Criar pipeline de pré-processamento (`StandardScaler` + `OneHotEncoder`), com `fit` **só no Train**.
9. [ ] Treinar o `Perceptron` no `X_train_prep`.
10. [ ] Avaliar no `X_val_prep`: accuracy, precision, recall, F1, matriz de confusão.
11. [ ] Só no final, avaliar no `X_test_prep`.
12. [ ] Interpretar resultados considerando o desbalanceamento das classes (não confiar só na accuracy).

---

## 8. Conceitos-chave para lembrar na hora da prova

- **Perceptron = soma ponderada + ativação.**
- **Erro guia a atualização dos pesos:** `w ← w + η·erro·x`.
- **Perceptron só separa fronteiras lineares** — limitação que motiva redes multicamadas.
- **Nunca ajustar transformações (scaler/encoder) usando dados de Val ou Test.**
- **Nunca usar variáveis que só existiriam "no futuro" em relação à previsão (leakage).**
- **Acurácia pode enganar em dados desbalanceados** — sempre olhar precision/recall/F1/matriz de confusão.
- **Estratificação (`stratify=y`)** mantém a proporção de classes em cada split.
