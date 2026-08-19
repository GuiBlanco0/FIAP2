import React from 'react';
import { View, Text, Image, StyleSheet, FlatList } from 'react-native';
import { Cartao } from './Cartao';

const pessoas = [
  {
    id: '1',
    nome: 'Anderson Silva',
    cargo: 'Aluno de Ciência da Computação',
    foto: require('./assets/dogs.jpg'),
  },
  {
    id: '2',
    nome: 'Beatriz Lima',
    cargo: 'Aluna de Engenharia de Software',
    foto: require('./assets/dogs.jpg'),
  },
  {
    id: '3',
    nome: 'Rodrigo Moraes',
    cargo: 'Professor',
    foto: require('./assets/dogs.jpg'),
  },
  {
    id: '4',
    nome: 'Hiago Perdido',
    cargo: 'Estudante',
    foto: require('./assets/dogs.jpg'),
  },
  {
    id: '5',
    nome: 'Thiago Achado',
    cargo: 'Ex estudante',
    foto: require('./assets/dogs.jpg'),
  }

];


export default function App() {
  return (

    <FlatList
      data={pessoas}
      keyExtractor={(item) => item.id}
      renderItem={({ item }) => (
        <Cartao
          nome={item.nome}
          cargo={item.cargo}
          foto={item.foto}
        />
      )}
      contentContainerStyle={styles.container}
    />

  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#060922',
  },
});