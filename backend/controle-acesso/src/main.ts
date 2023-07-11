import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import { DocumentBuilder, SwaggerModule } from '@nestjs/swagger';
import { ValidationPipe } from '@nestjs/common';

async function bootstrap() {
  const app = await NestFactory.create(AppModule);

  app.useGlobalPipes(new ValidationPipe({
    whitelist: true,
    transform: true,
    forbidNonWhitelisted: true, 
    transformOptions: {
      enableImplicitConversion: true,
    }
  }));

  const options = new DocumentBuilder()
    .setTitle('Aplicação de Controle de Acesso')
    .setDescription('Versão 0.0.1')
    .setVersion('0.0.1')
    .build(); 

  const document = SwaggerModule.createDocument(app, options); 
  SwaggerModule.setup('api', app, document);

  await app.listen(3000);
}

bootstrap();
