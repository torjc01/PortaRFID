import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { AcessoModule } from './acesso/acesso.module';
import { TypeOrmModule } from '@nestjs/typeorm';

// Configurer dotenv
const dotenv = require('dotenv');
dotenv.config();

// Configurer variables d'environnement
const POSTGRES_TYPE       = process.env.POSTGRES_TYPE;
const POSTGRES_HOST       = process.env.POSTGRES_HOST;
const POSTGRES_PORT       = process.env.POSTGRES_PORT;
const POSTGRES_DATABASE   = process.env.POSTGRES_DATABASE;
const POSTGRES_USER       = process.env.POSTGRES_USER;
const POSTGRES_PASSWORD   = process.env.POSTGRES_PASSWORD;

@Module({
  imports: [AcessoModule, 
    TypeOrmModule.forRoot({
      type: "postgres",
      host: "acs-backend-db",  
      port: 5432, 
      username: "acs-user", 
      password: POSTGRES_PASSWORD, 
      database: "acs-backend-db", 
      autoLoadEntities: true, 
      synchronize: true  // Disable when in production environment
      }),],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
