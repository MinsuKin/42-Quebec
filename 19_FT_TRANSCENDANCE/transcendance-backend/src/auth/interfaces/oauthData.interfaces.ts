export interface OauthData {
  id: string;
  email: string;
  username: string;
  from: 'google' | 'facebook' | 'github' | '42';
  profile: {
    firstName: string;
    lastName: string;
    avatar: string;
  };
  data: {
    accessToken: string;
    refreshToken: string;
  };
}
