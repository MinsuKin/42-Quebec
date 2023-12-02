import { faker } from '@faker-js/faker';
import * as argon from 'argon2';
import { PrismaClient } from '@prisma/client';

const prisma = new PrismaClient();

const serverBaseUrl = '/uploads';
async function main() {
  try {
    const usersPassword = await argon.hash('NotSecure1234');
    const userPromises = Array(15)
      .fill(null)
      .map((val, index) => {
        return prisma.user.upsert({
          where: { id: index + 1 },
          update: {},
          create: {
            username: faker.internet.userName(),
            email: faker.internet.email(),
            password: usersPassword,
            profile: {
              create: {
                name: faker.person.firstName(),
                lastname: faker.person.lastName(),
                avatar: getRandomUserAvatarUrl(),
                bio: faker.person.bio(),
              },
            },
          },
        });
      });
    const users = await Promise.all(userPromises);

    const chatRoomPromises = [
      prisma.chatRoom.upsert({
        where: { id: 1 },
        update: {},
        create: {
          name: 'Attack on Pong land',
          type: 'PUBLIC',
          avatar: `/uploads/room/fortnite.jpg`,
          members: {
            createMany: {
              data: [
                { memberId: 1, role: 'OWNER' },
                { memberId: 2, role: 'ADMIN' },
                { memberId: 3, role: 'ADMIN' },
                { memberId: 4, role: 'USER' },
                { memberId: 5, role: 'USER' },
                { memberId: 6, role: 'USER' },
                { memberId: 7, role: 'BAN' },
              ],
            },
          },
        },
      }),
      prisma.chatRoom.upsert({
        where: { id: 2 },
        update: {},
        create: {
          name: 'Pongistes',
          type: 'PUBLIC',
          avatar: `/uploads/room/pong_table.png`,
          members: {
            createMany: {
              data: [
                { memberId: 3, role: 'OWNER' },
                { memberId: 6, role: 'USER' },
                { memberId: 1, role: 'USER' },
                { memberId: 9, role: 'USER' },
                { memberId: 8, role: 'USER' },
                { memberId: 10, role: 'USER' },
              ],
            },
          },
        },
      }),
    ];
    await Promise.all(chatRoomPromises);

    const contactPromises = users.map((user, index) => {
      // Choose 2 random other users to add as contacts
      const contactIndices = [];
      while (contactIndices.length < 2) {
        const randomIndex = faker.number.int({
          min: 0,
          max: users.length - 1,
        });
        if (randomIndex !== index && !contactIndices.includes(randomIndex)) {
          contactIndices.push(randomIndex);
        }
      }
      // Create contact records
      return contactIndices.map((i) => {
        return prisma.contact.create({
          data: {
            userId: user.id,
            contactId: users[i].id,
          },
        });
      });
    });
    await Promise.all(contactPromises);
  } catch (e) {
    console.error('Error seeding the database:', e);
  } finally {
    console.log('Seeding finished.');
  }
}

function getRandomUserAvatarUrl(): string {
  const list = [
    'randomAvatars/icons8-bart-simpson-500.png',
    'randomAvatars/icons8-batman-500.png',
    'randomAvatars/icons8-character-500.png',
    'randomAvatars/icons8-deadpool-500.png',
    'randomAvatars/icons8-dj-500.png',
    'randomAvatars/icons8-finn-500.png',
    'randomAvatars/icons8-futurama-bender-500.png',
    'randomAvatars/icons8-homer-simpson-500.png',
    'randomAvatars/icons8-lisa-simpson-500.png',
    'randomAvatars/icons8-marge-simpson-500.png',
    'randomAvatars/icons8-owl-500.png',
    'randomAvatars/icons8-unicorn-500.png',
  ];
  const image = list[Math.floor(Math.random() * list.length)];
  return `${serverBaseUrl}/${image}`;
}
main()
  .then(async () => {
    await prisma.$disconnect();
  })
  .catch(async (e) => {
    console.error(e);
    await prisma.$disconnect();
    process.exit(1);
  });
