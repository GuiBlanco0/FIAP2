import React from 'react';
import { View, Text, Image, StyleSheet } from 'react-native';

export function Cartao({ nome, cargo, foto }) {
    return (

        <View style={styles.card}>
            <Image source={foto} style={styles.foto} />
            <Text style={styles.nome}>{nome}</Text>
            <Text style={styles.cargo}>{cargo}</Text>
        </View>

    );
}

const styles = StyleSheet.create({
    card: {
        backgroundColor: '#fff',
        padding: 20,
        borderRadius: 16,
        borderColor: '#333',
        borderWidth: 1,
        width: 350,
        alignItems: 'center',
        marginTop: 12
    },
    foto: {
        width: 100,
        height: 100,
        borderRadius: 50,
        marginBottom: 12,
    },
    nome: {
        fontSize: 24,
        fontWeight: 'bold',
    },
    cargo: {
        fontSize: 14,
        color: '#555',
        marginTop: 4,
    }
});