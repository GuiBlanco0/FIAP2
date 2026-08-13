readme_content = """# 📱 Meu Primeiro App em React Native & Expo! 🎉

> *"Todo grande desenvolvedor começou com um 'Hello World' ou um cartão de visitas digital."*

Bem-vindo ao repositório do meu primeiro aplicativo desenvolvido mobile com **React Native** e **Expo**! 

Este projeto é um **Cartão de Perfil Digital** simples, elegante e moderno, criado para praticar os conceitos fundamentais de estilização, componentes, layout com Flexbox e estruturação de projetos mobile.

---

## 🛠️ Tecnologias Utilizadas

![React Native](https://img.shields.io/badge/React_Native-20232A?style=for-the-badge&logo=react&logoColor=61DAFB)
![Expo](https://img.shields.io/badge/Expo-000000?style=for-the-badge&logo=expo&logoColor=white)
![JavaScript](https://img.shields.io/badge/JavaScript-F7DF1E?style=for-the-badge&logo=javascript&logoColor=black)

---

## ✨ Funcionalidades e Aprendizados

- [x] **Componentização**: Uso dos componentes fundamentais do React Native (`View`, `Text`, `Image`, `StatusBar`).
- [x] **Estilização com StyleSheet**: Aplicação de layout escuro (*Dark Mode*), bordas arredondadas (*avatar circular*), tipografia e espaçamentos.
- [x] **Flexbox no Mobile**: Alinhamento centralizado vertical e horizontalmente.
- [x] **Integração de Recursos Locais**: Carregamento de imagens locais via `require()`.
- [x] **Símbolos Unicode**: Utilização de caracteres Unicode para ícones de contato (email e telefone).

---

## 💻 Código Principal (`App.js`)

```javascript
import { StatusBar } from 'expo-status-bar';
import { StyleSheet, Text, View, Image } from 'react-native';

export default function App() {
  return (
    <View style={styles.container}>
      <Image source={require('./assets/dogs.jpg')} style={styles.foto} />
      <Text style={styles.titulo}>João Azevedo Alves</Text>
      <Text style={styles.subtitulo}>Estudante - FIAP</Text>
      <Text style={styles.textoInfo}>{"\\u2709"} gostodeprogramar@gmail.com</Text>
      <Text style={styles.textoInfo}>{"\\u260E"} 954619584</Text>
      <StatusBar style="light" />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#000000',
    alignItems: 'center',
    justify: 'center',
  },
  titulo: {
    color: '#fff',
    fontSize: 32,
    fontWeight: '500',
  },
  subtitulo: {
    color: '#fff',
    fontSize: 22,
    marginTop: 8,
    fontWeight: '200',
  },
  textoInfo: {
    color: '#aaa',
    marginTop: 8,
  },
  foto: {
    width: 300,
    height: 300,
    borderRadius: 999,
    marginBottom: 12,
  },
});
