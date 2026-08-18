# Aula 03 — LAN, Switch, Gateway, MAC e ARP

## 📚 Disciplina

**Sistemas Operacionais e Redes de Computadores**

## 🎯 Objetivo

Nesta aula prática, foi montada e configurada uma rede LAN utilizando o **Cisco Packet Tracer**, com:

* 3 computadores
* 1 Switch 2960
* 1 Roteador
* Configuração de IP e gateway
* SVI para gerenciamento do switch
* Tabela MAC
* Cache ARP
* Testes de conectividade com `ping`

A prática teve como foco compreender a comunicação dentro de uma rede local e a função do **switch, roteador, endereço MAC, ARP e gateway**.

---

## 🌐 Topologia

```text
PC0 ── Fa0/1 ┐
PC1 ── Fa0/2 ├── SW1 ── Fa0/24 ── R1
PC2 ── Fa0/3 ┘
```

### Endereçamento

| Dispositivo  | IP            | Máscara       | Gateway      |
| ------------ | ------------- | ------------- | ------------ |
| R1 (G0/0)    | 192.168.10.1  | 255.255.255.0 | —            |
| SW1 (VLAN 1) | 192.168.10.2  | 255.255.255.0 | 192.168.10.1 |
| PC0          | 192.168.10.10 | 255.255.255.0 | 192.168.10.1 |
| PC1          | 192.168.10.20 | 255.255.255.0 | 192.168.10.1 |
| PC2          | 192.168.10.30 | 255.255.255.0 | 192.168.10.1 |

A rede utilizada foi `192.168.10.0/24`.

---

## 🔌 Conexões

Foi utilizado **Copper Straight-Through** para realizar as conexões:

* PC0 → SW1 Fa0/1
* PC1 → SW1 Fa0/2
* PC2 → SW1 Fa0/3
* SW1 Fa0/24 → R1 G0/0

---

## 🔧 Configuração do Switch

Primeiramente, o switch recebeu nome, senhas e criptografia:

```bash
enable
configure terminal

hostname SW1
enable secret cisco123

line console 0
password con123
login
exit

line vty 0 15
password vty123
login
exit

service password-encryption
```

### SVI — VLAN 1

A interface VLAN 1 recebeu um endereço IP para permitir o gerenciamento do switch:

```bash
interface vlan 1
ip address 192.168.10.2 255.255.255.0
no shutdown
exit

ip default-gateway 192.168.10.1
```

Depois, a configuração foi salva:

```bash
copy running-config startup-config
```

A **SVI** fornece um IP de gerenciamento ao switch, mas não transforma o switch de camada 2 em um roteador.

---

## 🚦 Configuração do Roteador

O roteador foi configurado como **gateway padrão** da rede:

```bash
enable
configure terminal

hostname R1

interface g0/0
ip address 192.168.10.1 255.255.255.0
no shutdown
exit

copy running-config startup-config
```

O comando `no shutdown` é necessário para ativar a interface do roteador.

---

## 💻 Configuração dos PCs

Cada computador foi configurado manualmente com IP estático:

### PC0

```text
IP:      192.168.10.10
Máscara: 255.255.255.0
Gateway: 192.168.10.1
```

### PC1

```text
IP:      192.168.10.20
Máscara: 255.255.255.0
Gateway: 192.168.10.1
```

### PC2

```text
IP:      192.168.10.30
Máscara: 255.255.255.0
Gateway: 192.168.10.1
```

---

## 🧪 Testes de conectividade

Antes de gerar tráfego, a tabela MAC do switch e o cache ARP estavam vazios.

```bash
show mac address-table
```

No PC0:

```bash
arp -a
```

Após gerar tráfego, foram realizados testes de `ping` entre os dispositivos.

Exemplo:

```bash
ping 192.168.10.20
ping 192.168.10.1
ping 192.168.10.2
ping 192.168.10.30
```

Os testes esperados apresentaram **0% de perda de pacotes**.

---

## 🔢 Tabela MAC

Depois dos testes, o switch aprendeu os endereços MAC dos dispositivos conectados.

Comando utilizado:

```bash
show mac address-table
```

Exemplo:

```text
Vlan   Mac Address        Type      Ports
1      0060.2f1a.10ab    DYNAMIC   Fa0/1
1      0002.16c3.20cd    DYNAMIC   Fa0/2
1      00d0.58e7.30ef    DYNAMIC   Fa0/3
1      00e0.b0a1.24ff    DYNAMIC   Fa0/24
```

O switch associa **MAC ↔ porta**, permitindo encaminhar os quadros para a porta correta.

> Os endereços MAC podem ser diferentes no Packet Tracer. O importante é observar a associação entre o MAC e a porta.

---

## 🔎 ARP

No PC0 foi utilizado:

```bash
arp -a
```

Após a comunicação, o computador passou a possuir associações entre **IP e MAC**:

```text
192.168.10.1  → MAC do roteador
192.168.10.20 → MAC do PC1
192.168.10.30 → MAC do PC2
```

Diferentemente da tabela MAC do switch, o **ARP é utilizado pelo host para descobrir o endereço MAC associado a um endereço IP**.

---

## 📡 ARP no modo Simulation

No modo **Simulation**, foram filtrados apenas:

* ARP
* ICMP

Com o cache ARP limpo:

```bash
arp -d
```

Foi realizado um ping do PC0 para o PC1.

O processo observado foi:

```text
PC0
 │
 │ ARP Request (Broadcast)
 ▼
SW1
 │
 ├── PC1
 ├── PC2
 └── R1
      ↓
   ARP Reply (Unicast)
      ↓
     PC0
      ↓
   ICMP / Ping
```

O **ARP Request** é enviado em broadcast e o dispositivo que possui o IP solicitado responde com um **ARP Reply em unicast**. Depois disso, ocorre a comunicação utilizando ICMP.

---

## 🧠 Conceitos aprendidos

### Switch

Trabalha principalmente na **camada 2** e utiliza endereços MAC para encaminhar quadros.

```text
MAC → Porta
```

### ARP

Faz a resolução entre endereços IP e MAC.

```text
IP → MAC
```

### Gateway

É o dispositivo utilizado como saída da rede local para alcançar outras redes.

Neste laboratório:

```text
Gateway = 192.168.10.1
```

### SVI

A **Switch Virtual Interface (SVI)** fornece um endereço IP para gerenciamento do switch.

```text
SVI VLAN 1 = 192.168.10.2
```

---

## ⚠️ Solução de problemas

| Problema                          | Possível causa                      |
| --------------------------------- | ----------------------------------- |
| Tabela MAC vazia                  | Ainda não houve tráfego             |
| Gateway não responde              | Gateway incorreto ou G0/0 desligada |
| SVI não responde                  | VLAN 1 desligada                    |
| `show mac address-table` recusado | Não está no modo privilegiado       |
| ARP Request não aparece           | MAC já está no cache                |
| Enlace vermelho/laranja           | Cabo ou porta incorreta             |

---

## 📌 Resumo

Nesta prática foi montada uma **LAN com três PCs, um switch e um roteador**.

Foram trabalhados os principais conceitos:

* Endereçamento IPv4
* Máscara de rede
* Gateway padrão
* Switch de camada 2
* SVI
* Endereços MAC
* Tabela MAC
* ARP
* Broadcast e Unicast
* ICMP/Ping
* Cisco Packet Tracer

A principal diferença observada foi:

```text
Tabela MAC → MAC ↔ Porta
Cache ARP  → IP ↔ MAC
Gateway    → Saída para outras redes
SVI        → IP de gerenciamento do switch
```

---

## ✅ Checklist

* [x] 3 PCs conectados ao switch
* [x] Switch configurado
* [x] SVI VLAN 1 configurada
* [x] Gateway configurado
* [x] Roteador configurado
* [x] PCs configurados com IP estático
* [x] Conectividade testada com `ping`
* [x] Tabela MAC verificada
* [x] Cache ARP verificado
* [x] ARP observado no modo Simulation
