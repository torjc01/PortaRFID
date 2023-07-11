import { Injectable, NotFoundException, Query } from '@nestjs/common';
import { CreateAcessoDto } from './dto/create-acesso.dto';
import { UpdateAcessoDto } from './dto/update-acesso.dto';
import { PaginationQueryDto } from 'src/common/dto/pagination-query.dto/pagination-query.dto';
import { Acesso } from './entities/acesso.entity';
import { Repository } from 'typeorm';
import { InjectRepository } from '@nestjs/typeorm';
import { FindAcessoDto } from 'src/common/dto/find-acesso.dto/find-acesso.dto';

@Injectable()
export class AcessoService {

  /**
   * 
   * @param acessoRepository 
   */
  constructor(
    @InjectRepository(Acesso)
        private readonly acessoRepository: Repository<Acesso>,
  ){}

  /**
   * 
   * @param createAcessoDto 
   * @returns 
   */
  async create(createAcessoDto: CreateAcessoDto) {
    const acesso = this.acessoRepository.create(createAcessoDto);
  return this.acessoRepository.save(acesso);
  }

  /**
   * 
   * @param paginationQuery 
   * @returns 
   */
  findAll(paginationQuery: PaginationQueryDto) {
    const { limit, offset } = paginationQuery; 
      return this.acessoRepository.find({
          skip: offset, 
          take: limit
      });
  }
  
  /**
   * 
   * @param codigoRFID 
   * @param localizacao 
   * @returns 
   */
  /*async findAcessy(findAcessoQuery: FindAcessoDto){
    const {codigoRFID, localizacao} = findAcessoQuery;
    const acesso = await this.acessoRepository.findOne({
      where: {codigoRFID: codigoRFID, localizacao: localizacao }, 
    });

    if(!acesso){
        throw new NotFoundException(`Acesso do cartão ${codigoRFID} para a porta ${localizacao} não localizado`); 
    }
    return acesso;
  }
*/


  /**
   * 
   * @param id 
   * @param updateAcessoDto 
   * @returns 
   */
  update(id: string, updateAcessoDto: UpdateAcessoDto) {
    return this.acessoRepository.save(updateAcessoDto); 
  }

  /**
   * 
   * @param id 
   * @returns 
   */
  async findOne(id: number) {
    const acesso = await this.acessoRepository.findOne({
      where: {id: +id }, 
    });

    if(!acesso){
        throw new NotFoundException(`Acesso #${id} not found`); 
    }
    return acesso;
  }


  /**
   * 
   * @param id 
   * @returns 
   */
  async remove(id: number) {
    const acesso = await this.findOne(id); 
    return this.acessoRepository.remove(acesso);
  }

  /**
   * Filtra os acessos pelo critério de pesquisa codigoRFID (identificador da tag) e codigoIdPorta (identificador da porta)
   * @param codigoRFID 
   * @param localizacao 
   * @returns 
   */
  async filtraAcesso(codigoRFID: string, codigoIdPorta: string): Promise<Acesso[]> {
    console.log("[service] codigoRFID: ", codigoRFID);
    console.log("[service] localizacao: ", codigoIdPorta);
    let acessos = await this.acessoRepository.find({ 
      where: { codigoRFID, codigoIdPorta},
    });

    try {
      console.log(`[service] Concessão de acesso para [${acessos[0].nome} ${acessos[0].sobrenome}] na porta [${codigoIdPorta}] pela tag [${codigoRFID}]`)
    } catch (error) {
      acessos = null; 
      console.log(`[service] Erro: Acesso do cartão ${codigoRFID} para a porta ${codigoIdPorta} não localizado`);
      throw new NotFoundException(`[service] Acesso do cartão ${codigoRFID} para a porta ${codigoIdPorta} não localizado`);
    }
    
    return acessos;
  }
}
