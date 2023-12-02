import { Injectable } from '@nestjs/common';
import { PrismaService } from 'src/prisma/prisma.service';
import {
  Prisma,
  Notification,
  NotificationType,
  NotificationStatus,
} from '@prisma/client';

@Injectable()
export class NotificationRepository {
  constructor(private readonly prisma: PrismaService) {}

  async createNotification(
    data: Prisma.NotificationCreateInput,
  ): Promise<Notification> {
    return this.prisma.notification.create({ data });
  }

  async getNotificationsForUser(
    userId: number,
    params?: {
      skip?: number;
      take?: number;
      status?: NotificationStatus;
    },
  ): Promise<Notification[]> {
    return this.prisma.notification.findMany({
      where: {
        userId,
        ...(params?.status && { status: params.status }),
      },
      skip: params?.skip,
      take: params?.take,
      orderBy: { createdAt: 'desc' },
    });
  }

  async markNotificationAsRead(notificationId: number): Promise<Notification> {
    return this.prisma.notification.update({
      where: { id: notificationId },
      data: { status: NotificationStatus.READ },
    });
  }

  async deleteNotification(notificationId: number): Promise<Notification> {
    return this.prisma.notification.delete({ where: { id: notificationId } });
  }
}
