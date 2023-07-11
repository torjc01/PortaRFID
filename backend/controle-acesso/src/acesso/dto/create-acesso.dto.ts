import { ApiProperty } from "@nestjs/swagger";
import { IsString } from "class-validator";


export class CreateAcessoDto {

    @ApiProperty({description: "Código identificador de tag RFID", example: "04 20 49 0A ED 49 85"})
    @IsString()
    readonly codigoRFID: string; 

    @ApiProperty({description: "Nome do proprietário da tag", example: "José"})
    @IsString()
    readonly nome: string; 

    @ApiProperty({description: "Sobrenome do proprietário da tag", example: "da Silva"})
    @IsString()
    readonly sobrenome: string; 

    @ApiProperty({description: "Localizacao da porta", example: "Porta de entrada principal"})
    @IsString()
    readonly localizacao: string; 

    @ApiProperty({description: "Codigo de identificação da porta", example: "A01"})
    @IsString()
    readonly codigoIdPorta: string; 
}
