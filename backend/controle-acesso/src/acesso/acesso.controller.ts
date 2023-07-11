import { Controller, Get, Post, Body, Patch, Param, Delete, Query, NotFoundException } from '@nestjs/common';
import { AcessoService } from './acesso.service';
import { CreateAcessoDto } from './dto/create-acesso.dto';
import { UpdateAcessoDto } from './dto/update-acesso.dto';
import { ApiForbiddenResponse, ApiTags } from '@nestjs/swagger';
import { PaginationQueryDto } from 'src/common/dto/pagination-query.dto/pagination-query.dto';
import { Acesso } from './entities/acesso.entity';


@ApiTags('acesso')
@Controller('acesso')
export class AcessoController {

  constructor(private readonly acessoService: AcessoService) {}

  @Post()
  @ApiForbiddenResponse({ description: 'Proibido.'})
  create(@Body() createAcessoDto: CreateAcessoDto) {
    return this.acessoService.create(createAcessoDto);
  }

  @Get()
  @ApiForbiddenResponse({ description: 'Proibido.'})
  findAll(@Query() paginationQuery: PaginationQueryDto) {
    return this.acessoService.findAll(paginationQuery);
  }

  /*
  @Get(':id')
  @ApiForbiddenResponse({ description: 'Proibido.'})
  findOne(@Param('id') id: string) {
    return this.acessoService.findOne(+id);
  }*/

  @Get('/filtra')
  @ApiForbiddenResponse({ description: 'Proibido.'})
  async filtraAcesso(
    @Query('codigoRFID') codigoRFID: string,
    @Query('codigoIdPorta') codigoIdPorta: string,
  ): Promise<Acesso[]> {
    console.log("[controller] codigoRFID: ", codigoRFID);
    console.log("[controller] codigoIdPorta: ", codigoIdPorta);

    const acessos = await this.acessoService.filtraAcesso(codigoRFID, codigoIdPorta); 

    if (!acessos ){
      console.log("Nao acessos...");
      throw new NotFoundException(); 
    }
    return acessos;
  }

  @Patch(':id')
  @ApiForbiddenResponse({ description: 'Proibido.'})
  update(@Param('id') id: string, @Body() updateAcessoDto: UpdateAcessoDto) {
    return this.acessoService.update(id, updateAcessoDto);
  }

  @Delete(':id')
  @ApiForbiddenResponse({ description: 'Proibido.'})
  remove(@Param('id') id: string) {
    return this.acessoService.remove(+id);
  }
}
