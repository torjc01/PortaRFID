echo "Instalação das dependências de desenvolvimento para NestJS"

echo "Deps da documentacao: Swagger"
npm i @nestjs/swagger swagger-ui-express

echo "Deps da validação"
npm i class-validator class-transformer
npm i @nestjs/mapped-types

echo "Deps do banco de dados e do ORM"
npm i @nestjs/typeorm typeorm pg
