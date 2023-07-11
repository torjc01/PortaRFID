import { Module } from '@nestjs/common';
import { AcessoService } from './acesso.service';
import { AcessoController } from './acesso.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Acesso } from './entities/acesso.entity';

@Module({
  controllers: [AcessoController],
  imports: [TypeOrmModule.forFeature([Acesso])],
  exports: [TypeOrmModule, AcessoService],
  providers: [AcessoService]
})
export class AcessoModule {}
