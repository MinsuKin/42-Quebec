import { Injectable } from '@nestjs/common';
import fetch from 'node-fetch';

export interface Coalition {
  id: number;
  name: string;
  slug: string;
  image_url: string;
  color: string;
  score: number;
  user_id: number;
}

@Injectable()
export class SchoolNetworkService {
  async getCoalitions(access_token: string, userId: string | number) {
    const link = `https://api.intra.42.fr/v2/users/${userId}/coalitions`;
    try {
      const response = await fetch(link, {
        method: 'GET',
        headers: {
          Authorization: `Bearer ${access_token}`,
        },
      });
      if (!response.ok) {
        console.log(
          `Failed to fetch coalitions from 42. Status code: ${response.status}`,
        );
      }
      const data: Coalition[] = await response.json();
      return data;
    } catch (e) {
      return [];
    }
  }
}
