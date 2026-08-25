# Anotações da Aula 4

## Configuração

* Cabo azul

  * **RS232 → Console**

## Comandos

### Dentro do terminal do computador

```bash
# Habilitar o modo privilegiado
enable

# Entrar no modo de configuração global
configure terminal

# Nomear o Switch
hostname (Nome Indicado)

# Habilitar senha para o modo privilegiado
enable password (Senha 1)

# Habilitar senha criptografada para o modo privilegiado
enable secret (Senha Criptografada)

# Habilitar senha do modo console
line console 0
password (Senha 1)
login

# Habilitar modo Telnet/VTY
line vty 0 4
password (Senha 1)
login

# Colocar mensagem de alerta ao entrar na área restrita
banner motd #AREA RESTRITA - WARNING#

# Configuração da VLAN 1
interface vlan 1
ip address (IP INDICADO) 255.255.255.0
no shutdown

# O Switch se torna pingável

# Criptografar as senhas atuais e futuras
# Testar com "show running-config"
service password-encryption

# Voltar ao modo privilegiado
exit
# ou
end

# Salvar a configuração da RAM para a NVRAM
copy running-config startup-config
```

## Configuração do Segundo Switch

Para configurar o segundo Switch:

1. Repetir os mesmos comandos utilizados no primeiro Switch.
2. Alterar o **hostname**.
3. Alterar as **senhas**, caso necessário.
4. Copiar e colar os comandos no segundo computador/Switch.
5. Configurar os **IPs e Gateways** conforme indicado na atividade.

---

## Comandos Úteis

```bash
# Exibir a configuração atual
show running-config

# Configurar o gateway padrão
ip default-gateway (Gateway)
```

> `ip default-gateway` deve ser utilizado no **modo de configuração global**.

---

## Perguntas Possíveis

### Para que serve um gateway no Switch?

O **gateway** permite que o Switch consiga se comunicar com dispositivos que estão **fora da sua própria rede local**.

Por exemplo, quando o Switch precisa ser acessado a partir de outra rede, ele utiliza o **gateway padrão** para encaminhar esse tráfego para fora da sua rede.

### Resumo

* **IP:** identifica o Switch na rede.
* **Máscara de sub-rede:** determina qual é a rede à qual o Switch pertence.
* **Gateway:** permite a comunicação com outras redes.
* **VLAN 1:** interface virtual utilizada para gerenciamento do Switch.
