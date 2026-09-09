import { View, Text, Image, StyleSheet } from 'react-native';

export default function ItemCardapio({ foto, nome, descricao, preco }) {
  return (
    <View style={styles.item}>
      <Image source={foto} style={styles.foto} />

      <View style={styles.info}>
        <Text style={styles.nome}>{nome}</Text>
        <Text style={styles.descricao}>{descricao}</Text>
      </View>

      <Text style={styles.preco}>{preco}</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  item: {
    flexDirection: 'row',
    alignItems: 'center',
    backgroundColor: '#018538',
    borderRadius: 12,
    padding: 12,
    marginBottom: 16,
    borderColor: '#ffffff',
    borderWidth: 1,
    margin: 10
  },
  foto: { width: 70, height: 70, borderRadius: 8 },
  info: { flex: 1, marginLeft: 12 },
  nome: { fontSize: 16, fontWeight: 'bold'},
  descricao: { fontSize: 13, color: '#202020' },
  preco: { fontSize: 16, fontWeight: 'bold', color: '#018538' },
});