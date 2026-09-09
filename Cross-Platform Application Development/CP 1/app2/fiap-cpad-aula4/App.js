import { View, Image, FlatList, StyleSheet } from 'react-native';
import ItemCardapio from './ItemCardapio';
import { cardapio } from './cardapio';

export default function App() {
  return (
    <View style={styles.container}>
      <Image source={require('./assets/img/logo.png')} style={styles.logo} />

      <FlatList
        style={styles.lista}
        data={cardapio}
        keyExtractor={(item) => item.id}
        renderItem={({ item }) => (
          <ItemCardapio
            foto={item.foto}
            nome={item.nome}
            descricao={item.descricao}
            preco={item.preco}
          />
        )}
      />
    </View>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1, backgroundColor: '#033f0b' },
  logo: { width: 250, height: 80, resizeMode: 'contain', alignSelf: 'center', marginTop: 20, borderRadius: 999 },
  lista: { flex: 3 },
});