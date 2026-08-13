import { StatusBar } from 'expo-status-bar';
import { StyleSheet, Text, View, Image } from 'react-native';

export default function App() {
  return (
    <View style={styles.container}>
      <Image source={require('./assets/dogs.jpg')} style={styles.foto}></Image>
      <Text style={styles.titulo}>João Azevedo Alves</Text>
      <Text style={styles.subtitulo}> Estudante - FIAP</Text>
      <Text style={styles.textoInfo}>{"\u2709"} gostodeprogramar@gmail.com</Text>
      <Text style={styles.textoInfo}>{"\u260E"} 954619584</Text>
      <StatusBar style="auto" />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#000000',
    alignItems: 'center',
    justifyContent: 'center',
  },
  titulo:{
    color:"#fff",
    fontSize: 32,
    fontWeight: 500,
  },
  subtitulo:{
    color: "#fff",
    fontSize: 22,
    marginTop: 8,
    fontWeight: 200,
  },
  textoInfo:{
    color: "#aaa",
    marginTop: 8,
  },
  foto:{
    width: 300,
    height: 300,
    borderRadius: 999,
    marginBottom: 12,
  }
});
