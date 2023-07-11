import { Column, Entity, PrimaryGeneratedColumn } from "typeorm";

@Entity()
export class Acesso {

    @PrimaryGeneratedColumn()
    id: number; 

    @Column({length: 32})
    codigoRFID: string; 

    @Column({length: 32})
    nome: string; 

    @Column({length: 32})
    sobrenome: string;

    @Column({length: 32})
    localizacao: string;
    
    @Column({length: 16, default: ' '})
    codigoIdPorta: string;

}
